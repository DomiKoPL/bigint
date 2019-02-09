////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

bool bigint_is_zero(const Bigint *big_int)
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