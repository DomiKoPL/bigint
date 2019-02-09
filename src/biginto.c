////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "fft.h"

Bigint *bigint_add(const Bigint *big_int, const Bigint *value)
{
	if (big_int->sign == MINUS && value->sign == MINUS)
	{
		// -A + -B = - (A + B)
		Bigint *res = bigint_minus(bigint_add(bigint_minus(big_int), bigint_minus(value)));
		bigint_trim(res);
		return res;
	}

	if (big_int->sign == PLUS && value->sign == PLUS)
	{
		int carry = 0;
		int max_len = big_int->len;
		if (value->len > max_len)
		{
			max_len = value->len;
		}

		Bigint *res = bigint_constructor();
		res->arr = (int *)malloc(max_len * sizeof(int));
		res->len = max_len;
		res->sign = PLUS;

		for (int i = 0; i < max_len; i++)
		{
			if (i < big_int->len)
			{
				carry += big_int->arr[i];
			}

			if (i < value->len)
			{
				carry += value->arr[i];
			}

			res->arr[i] = carry % bigint_base;
			carry /= bigint_base;
		}

		if (carry > 0)
		{
			int *copy = (int *)malloc((max_len + 1) * sizeof(int));
			for (int i = 0; i < max_len; i++)
				copy[i] = res->arr[i];
			copy[max_len] = carry;

			res->arr = copy;
			res->len++;
		}

		bigint_trim(res);
		return res;
	}

	if (big_int->sign == MINUS && value->sign == PLUS)
	{
		return bigint_add(value, big_int);
	}

	if (big_int->sign == PLUS && value->sign == MINUS)
	{
		// if A < abs(B)
		// it's hard to do 1 + -3, so I will make -(3 + -1)
		if (bigint_compare(big_int, bigint_abs(value)) == SMALLER)
		{
			// A + -B = -B + A = -(B + -A)
			return bigint_minus(bigint_add(bigint_abs(value), bigint_minus(big_int)));
		}

		// A > abs(B)

		Bigint *res = bigint_copy(big_int);

		for (int i = 0; i < value->len; i++)
		{
			if (value->arr[i] > res->arr[i])
			{
				res->arr[i] += bigint_base;
				res->arr[i + 1]--;
			}

			res->arr[i] -= value->arr[i];
		}

		for (int i = 0; i < value->len; i++)
		{
			if (res->arr[i] < 0)
			{
				res->arr[i] += bigint_base;
				res->arr[i + 1]--;
			}
		}

		bigint_trim(res);
		return res;
	}

	return bigint_constructor();
}

Bigint *bigint_addi(const Bigint *big_int, const int value)
{
	return bigint_add(big_int, bigint_constructori(value));
}

Bigint *bigint_addll(const Bigint *big_int, const long long value)
{
	return bigint_add(big_int, bigint_constructorll(value));
}

Bigint *bigint_addstr(const Bigint *big_int, const char *value)
{
	return bigint_add(big_int, bigint_constructorstr(value));
}

Bigint *bigint_sub(const Bigint *big_int, const Bigint *value)
{
	// A - B = A + (-B) #Trikowe
	return bigint_add(big_int, bigint_minus(value));
}

Bigint *bigint_subi(const Bigint *big_int, const int value)
{
	return bigint_sub(big_int, bigint_constructori(value));
}

Bigint *bigint_subll(const Bigint *big_int, const long long value)
{
	return bigint_sub(big_int, bigint_constructorll(value));
}

Bigint *bigint_substr(const Bigint *big_int, const char *value)
{
	return bigint_sub(big_int, bigint_constructorstr(value));
}

Bigint *bigint_mult(const Bigint *a, const Bigint *b)
{
	Bigint *res = bigint_constructor();

	if (bigint_is_zero(a) || bigint_is_zero(b))
	{
		return res;
	}

	if (a->sign != b->sign)
	{
		res->sign = MINUS;
	}

	int new_len = a->len * b->len + 1;
	res->len = new_len;
	res->arr = (int *)malloc(new_len * sizeof(int));

	for (int i = 0; i < a->len; i++)
	{
		for (int j = 0; j < b->len; j++)
		{
			long long temp = res->arr[i + j];
			temp += 1ll * a->arr[i] * b->arr[j];
			res->arr[i + j] = temp % bigint_base;
			temp /= bigint_base;
			res->arr[i + j + 1] += temp;
		}
	}

	for (int i = 0; i < res->len; i++)
	{
		if (res->arr[i] > bigint_base)
		{
			res->arr[i + 1] += res->arr[i] / bigint_base;
			res->arr[i] %= bigint_base;
		}
	}

	bigint_trim(res);
	return res;
}

Bigint *bigint_multi(const Bigint *a, const int b)
{
	return bigint_mult(a, bigint_constructori(b));
}

Bigint *bigint_multll(const Bigint *a, const long long b)
{
	return bigint_mult(a, bigint_constructorll(b));
}

Bigint *bigint_multfast(const Bigint *a, const Bigint *b)
{
	Bigint *res = bigint_constructor();

	fft_mult(a->arr, a->len, b->arr, b->len, &(res->arr), &(res->len), bigint_base);

	if (bigint_comparei(res, 0) == EQUAL)
		res->sign = PLUS;
	else
		res->sign = a->sign * b->sign;
		
	bigint_trim(res);

	return res;
}

Bigint *bigint_divmod(const Bigint *a, const Bigint *b, bool type)
{
	int norm = bigint_base / (b->arr[b->len - 1] + 1);
	Bigint *a1 = bigint_multi(bigint_abs(a), norm);
	Bigint *b1 = bigint_multi(bigint_abs(b), norm);
	Bigint *q, *r;

	q = bigint_constructor();
	r = bigint_constructor();

	q->sign = PLUS;
	bigint_resize(q, a->len);

	for (int i = a1->len - 1; i >= 0; i--)
	{
		r = bigint_multi(r, bigint_base);
		r = bigint_addi(r, a1->arr[i]);

		int s1 = r->len <= b1->len ? 0 : r->arr[b1->len];
		int s2 = r->len <= b1->len - 1 ? 0 : r->arr[b1->len - 1];
		int d = (1ll * bigint_base * s1 + s2) / b1->arr[b1->len - 1];

		r = bigint_sub(r, bigint_multi(b1, d));
		while (bigint_comparei(r, 0) == SMALLER)
		{
			r = bigint_add(r, b1);
			d--;
		}

		q->arr[i] = d;
	}

	q->sign = a1->sign * b1->sign;
	r->sign = a1->sign;

	bigint_trim(q);
	bigint_trim(r);

	if (type == 0)
	{
		return q;
	}
	else if (type == 1)
	{
		return bigint_divi(r, norm);
	}

	// WRONG TYPE
	return bigint_constructor();
}

Bigint *bigint_div(const Bigint *a, const Bigint *b)
{
	return bigint_divmod(a, b, 0);
}

Bigint *bigint_divi(const Bigint *a, const int b)
{
	Bigint *res = bigint_copy(a);
	int value = b;
	if (value < 0)
	{
		res = bigint_minus(res);
		value = -value;
	}

	long long carry = 0;
	for (int i = res->len - 1; i >= 0; i--)
	{
		carry *= bigint_base;
		carry += res->arr[i];
		res->arr[i] = carry / value;
		carry %= value;
	}

	bigint_trim(res);
	return res;
}

Bigint *bigint_mod(const Bigint *a, const Bigint *b)
{
	return bigint_divmod(a, b, 1);
}