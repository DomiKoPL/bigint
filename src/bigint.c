////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////
/// Base of Bigint
///
////////////////////////////////////////////////////////////
static const int bigint_base = 1000000000;

Bigint *bigint_constructor()
{
	Bigint *newBigint = (Bigint *)malloc(sizeof(Bigint));

	bigint_assigni(newBigint, 0);

	return newBigint;
}

Bigint *bigint_constructori(const int value)
{
	Bigint *newBigint = (Bigint *)malloc(sizeof(Bigint));

	bigint_assigni(newBigint, value);

	return newBigint;
}

Bigint *bigint_constructorll(const long long value)
{
	Bigint *newBigint = (Bigint *)malloc(sizeof(Bigint));

	bigint_assignll(newBigint, value);

	return newBigint;
}

Bigint *bigint_constructorstr(const char *value)
{
	Bigint *newBigint = (Bigint *)malloc(sizeof(Bigint));

	bigint_assignstr(newBigint, value);

	return newBigint;
}

void bigint_free(Bigint *big_int)
{
	free(big_int->arr);
	free(big_int);
}

Bigint *bigint_copy(const Bigint *big_int)
{
	Bigint *copy = (Bigint *)malloc(sizeof(Bigint));
	copy->arr = (int *)malloc(big_int->len * sizeof(int));
	copy->len = big_int->len;
	copy->sign = big_int->sign;
	for (int i = 0; i < big_int->len; i++)
		copy->arr[i] = big_int->arr[i];
	return copy;
}

void bigint_assign(Bigint *big_int, const Bigint *value)
{
	big_int = bigint_copy(value);
}

void bigint_assigni(Bigint *big_int, const int value)
{
	int val = value;
	big_int->sign = (val >= 0 ? PLUS : MINUS);
	if (val < 0)
		val = -val;

	int new_size = 1 + (val >= bigint_base ? 1 : 0);

	big_int->arr = (int *)malloc(new_size * sizeof(int));
	big_int->len = new_size;

	if (new_size == 1)
	{
		big_int->arr[0] = val;
	}
	else
	{
		big_int->arr[0] = val % bigint_base;
		big_int->arr[1] = val / bigint_base;
	}
}

void bigint_assignll(Bigint *big_int, const long long value)
{
	long long val = value;
	big_int->sign = (val >= 0 ? PLUS : MINUS);
	if (val < 0)
		val = -val;

	int new_size = 1;

	long long temp_val = val / bigint_base;
	while (temp_val > 0)
	{
		new_size++;
		temp_val /= bigint_base;
	}

	big_int->arr = (int *)malloc(new_size * sizeof(int));
	big_int->len = new_size;

	int cur_pos = 0;
	while (cur_pos < new_size)
	{
		big_int->arr[cur_pos++] = val % bigint_base;
		val /= bigint_base;
	}
}

void bigint_assignstr(Bigint *big_int, const char *value)
{
	int l_pos = 0;
	if (value[0] == '-')
	{
		l_pos = 1;
		big_int->sign = MINUS;
	}
	else
	{
		big_int->sign = PLUS;
	}

	int new_size = (strlen(value) + 8) / 9;
	big_int->len = new_size;
	big_int->arr = (int *)malloc(big_int->len * sizeof(int));
	int cur_pos = 0;
	for (int i = strlen(value) - 1; i >= l_pos; i -= 9)
	{
		int wsp = 0, pot = 1;
		for (int j = 0; j < 9 && i - j >= l_pos; j++)
		{
			int x = value[i - j] - '0';
			wsp += x * pot;
			pot *= 10;
		}
		big_int->arr[cur_pos++] = wsp;
	}
}

char *bigint_tostring(const Bigint *big_int)
{
	int pocz_len = snprintf(NULL, 0, "%d", big_int->arr[big_int->len - 1]);
	int len = (big_int->len - 1) * 9 + pocz_len;

	if (big_int->sign == MINUS)
	{
		len++;
	}

	char *str = (char *)malloc((len + 1) * sizeof(char));
	int cur_pos = 0;
	if (big_int->sign == MINUS)
	{
		str[cur_pos++] = '-';
	}

	snprintf(str + cur_pos, pocz_len + 1, "%d", big_int->arr[big_int->len - 1]);
	cur_pos += pocz_len;

	for (int i = big_int->len - 2; i >= 0; i--)
	{
		snprintf(str + cur_pos, 9 + 1, "%09d", big_int->arr[i]);
		cur_pos += 9;
	}

	return str;
}

void bigint_print(const Bigint *big_int)
{
	if (big_int->sign == MINUS)
		printf("-");

	printf("%d", big_int->arr[big_int->len - 1]);

	for (int i = big_int->len - 2; i >= 0; i--)
	{
		printf("%09d", big_int->arr[i]);
	}
}

void bigint_println(const Bigint *big_int)
{
	bigint_print(big_int);
	printf("\n");
}

void bigint_trim(Bigint *big_int)
{
	int new_size = big_int->len;
	while (new_size > 1 && big_int->arr[new_size - 1] == 0)
	{
		new_size--;
	}

	big_int->len = new_size;
	free(big_int->arr[new_size]);
}

Bigint *bigint_abs(const Bigint *big_int)
{
	Bigint *res = bigint_copy(big_int);
	res->sign = PLUS;
	return res;
}

Bigint *bigint_minus(const Bigint *big_int)
{
	Bigint *res = bigint_copy(big_int);

	if (res->sign == PLUS)
	{
		// 0 must be positive
		if (bigint_is_zero(big_int) == false)
		{
			res->sign = MINUS;
		}
	}
	else
	{
		res->sign = PLUS;
	}

	return res;
}

bool *bigint_is_zero(const Bigint *big_int)
{
	if (bigint_comparei(big_int, 0) == EQUAL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

short bigint_compare(const Bigint *A, const Bigint *B)
{
	if (A->sign != B->sign)
	{
		return A->sign;
	}

	// same sign
	if (A->len < B->len)
	{
		return -A->sign;
	}

	if (A->len > B->len)
	{
		return A->sign;
	}

	for (int i = A->len - 1; i >= 0; i--)
	{
		if (A->arr[i] > B->arr[i])
		{
			return A->sign;
		}

		if (A->arr[i] < B->arr[i])
		{
			return -A->sign;
		}
	}

	return 0; // equal
}

short bigint_comparei(const Bigint *A, const int B)
{
	return bigint_compare(A, bigint_constructori(B));
}

short bigint_comparell(const Bigint *A, const long long B)
{
	return bigint_compare(A, bigint_constructorll(B));
}

short bigint_comparestr(const Bigint *A, const char *B)
{
	return bigint_compare(A, bigint_constructorstr(B));
}

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