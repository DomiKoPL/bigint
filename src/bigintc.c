////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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

void bigint_resize(Bigint *big_int, const int new_size)
{
	big_int->len = new_size;
	big_int->arr = (int *)malloc(new_size * sizeof(int));
	for (int i = 0; i < new_size; i++)
	{
		big_int->arr[i] = 0;
	}
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

void bigint_trim(Bigint *big_int)
{
	int new_size = big_int->len;
	while (new_size > 1 && big_int->arr[new_size - 1] == 0)
	{
		new_size--;
	}

	if (big_int->len > new_size)
	{
		big_int->len = new_size;
		big_int = bigint_copy(big_int);
	}
}