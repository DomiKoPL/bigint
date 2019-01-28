////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "bigInt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////////////////////////////////////////
/// Base of bigInt
///
////////////////////////////////////////////////////////////
const int bigInt_base = 1000000000;

BigInt *bigInt_constructor()
{
	BigInt *newBigint = (BigInt *)malloc(sizeof(BigInt));

	bigInt_assigni(newBigint, 0);

	return newBigint;
}

BigInt *bigInt_constructori(const int value)
{
	BigInt *newBigint = (BigInt *)malloc(sizeof(BigInt));

	bigInt_assigni(newBigint, value);

	return newBigint;
}

BigInt *bigInt_constructorll(const long long value)
{
	BigInt *newBigint = (BigInt *)malloc(sizeof(BigInt));

	bigInt_assignll(newBigint, value);

	return newBigint;
}

BigInt *bigInt_constructorstr(const char *value)
{
	BigInt *newBigint = (BigInt *)malloc(sizeof(BigInt));

	bigInt_assignstr(newBigint, value);

	return newBigint;
}

void bigInt_free(BigInt *big_int)
{
	free(big_int->arr);
	free(big_int);
}

BigInt *bigInt_copy(const BigInt *big_int)
{
	BigInt *copy = (BigInt *)malloc(sizeof(BigInt));
	copy->arr = (int *)malloc(big_int->len * sizeof(int));
	copy->len = big_int->len;
	memcpy(copy->arr, big_int->arr, big_int->len * sizeof(int));
	return copy;
}

void bigInt_assign(BigInt *big_int, const BigInt *value)
{
	big_int = bigInt_copy(value);
}

void bigInt_assigni(BigInt *big_int, const int value)
{
	int val = value;
	big_int->sign = (val >= 0 ? PLUS : MINUS);
	if (val < 0)
		val = -val;

	int new_size = 1 + (val >= bigInt_base ? 1 : 0);

	big_int->arr = (int *)malloc(new_size * sizeof(int));
	big_int->len = new_size;

	if (new_size == 1)
	{
		big_int->arr[0] = val;
	}
	else
	{
		big_int->arr[0] = val % bigInt_base;
		big_int->arr[1] = val / bigInt_base;
	}
}

void bigInt_assignll(BigInt *big_int, const long long value)
{
	long long val = value;
	big_int->sign = (val >= 0 ? PLUS : MINUS);
	if (val < 0)
		val = -val;

	int new_size = 1;

	long long temp_val = val / bigInt_base;
	while (temp_val > 0)
	{
		new_size++;
		temp_val /= bigInt_base;
	}

	big_int->arr = (int *)malloc(new_size * sizeof(int));
	big_int->len = new_size;

	int cur_pos = 0;
	while (cur_pos < new_size)
	{
		big_int->arr[cur_pos++] = val % bigInt_base;
		val /= bigInt_base;
	}
}

void bigInt_assignstr(BigInt *big_int, const char *value)
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

char *bigInt_tostring(const BigInt *big_int)
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

void bigInt_print(const BigInt *big_int)
{
	if (big_int->sign == MINUS)
		printf("-");

	printf("%d", big_int->arr[big_int->len - 1]);

	for (int i = big_int->len - 2; i >= 0; i--)
	{
		printf("%09d", big_int->arr[i]);
	}
}

void bigInt_println(const BigInt *big_int)
{
	bigInt_print(big_int);
	printf("\n");
}

BigInt *bigInt_addi(const BigInt *big_int, const int value)
{
	if (value < 0)
	{
		return bigInt_subi(big_int, -value);
	}

	BigInt *res = bigInt_copy(big_int);

	int carry = value;
	for (int i = 0; i < res->len; i++)
	{
		carry += res->arr[i];
		res->arr[i] = carry % bigInt_base;
		carry /= bigInt_base;
	}

	if (carry > 0)
	{
		int *carr = (int *)malloc((res->len + 1) * sizeof(int));
		memcpy(carr, big_int->arr, res->len * sizeof(int));
		carr[res->len] = carry;
		res->arr = carr;
		res->len = res->len + 1;
	}

	return res;
}

BigInt *bigInt_addll(const BigInt *big_int, const long long value)
{
	if (value < 0)
	{
		return bigInt_subll(big_int, -value);
	}

	BigInt *res = bigInt_copy(big_int);

	long long carry = value;
	for (int i = 0; i < res->len; i++)
	{
		carry += res->arr[i];
		res->arr[i] = carry % bigInt_base;
		carry /= bigInt_base;
	}

	while (carry > 0)
	{
		int *carr = (int *)malloc((res->len + 1) * sizeof(int));
		memcpy(carr, big_int->arr, res->len * sizeof(int));
		carr[res->len] = carry;
		res->arr = carr;
		res->len = res->len + 1;
		carry /= bigInt_base;
	}

	return res;
}
BigInt *bigInt_subi(const BigInt *big_int, const int value)
{
	if (value < 0)
	{
		return bigInt_addi(big_int, -value);
	}
	//TODO
}

BigInt *bigInt_subll(const BigInt *big_int, const long long value)
{
	if (value < 0)
	{
		return bigInt_addll(big_int, -value);
	}
	//TODO
}
