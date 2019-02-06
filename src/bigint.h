#ifndef BIG_INT_H
#define BIG_INT_H
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdbool.h>

enum
{
	PLUS = 1,
	MINUS = -1
};

enum
{
	SMALLER = -1,
	EQUAL = 0,
	BIGGER = 1
};

typedef struct _Bigint
{
	int sign;
	int *arr;
	int len;
} Bigint;

Bigint *bigint_constructor();

Bigint *bigint_constructori(const int value);

Bigint *bigint_constructorll(const long long value);

Bigint *bigint_constructorstr(const char *value);

void bigint_free(Bigint *big_int);

Bigint *bigint_copy(const Bigint *big_int);

void bigint_resize(Bigint *big_int, const int new_size);

void bigint_assign(Bigint *big_int, const Bigint *value);

void bigint_assigni(Bigint *big_int, const int value);

void bigint_assignll(Bigint *big_int, const long long value);

void bigint_assignstr(Bigint *big_int, const char *value);

char *bigint_tostring(const Bigint *big_int);

void bigint_print(const Bigint *big_int);

void bigint_println(const Bigint *big_int);

///erase leading zeros
void bigint_trim(Bigint *big_int);

Bigint *bigint_abs(const Bigint *big_int);

Bigint *bigint_minus(const Bigint *big_int);

///return 1 if big_int is equal to 0, 0 otherwise
bool bigint_is_zero(const Bigint *big_int);

///return SMALLER if A < B, EQUAL if A == B, 1 if A > B
short bigint_compare(const Bigint *A, const Bigint *B);

///return SMALLER if A < B, EQUAL if A == B, BIGGER if A > B
short bigint_comparei(const Bigint *A, const int B);

///return SMALLER if A < B, EQUAL if A == B, BIGGER if A > B
short bigint_comparell(const Bigint *A, const long long B);

///return SMALLER if A < B, EQUAL if A == B, BIGGER if A > B
short bigint_comparestr(const Bigint *A, const char *B);

Bigint *bigint_add(const Bigint *big_int, const Bigint *value);

Bigint *bigint_addi(const Bigint *big_int, const int value);

Bigint *bigint_addll(const Bigint *big_int, const long long value);

Bigint *bigint_addstr(const Bigint *big_int, const char *value);

Bigint *bigint_sub(const Bigint *big_int, const Bigint *value);

Bigint *bigint_subi(const Bigint *big_int, const int value);

Bigint *bigint_subll(const Bigint *big_int, const long long value);

Bigint *bigint_substr(const Bigint *big_int, const char *value);

Bigint *bigint_mult(const Bigint *a, const Bigint *b);

Bigint *bigint_multi(const Bigint *a, const int b);

Bigint *bigint_multll(const Bigint *a, const long long b);

Bigint *bigint_multfast(const Bigint *a, const Bigint *b);

Bigint *bigint_divmod(const Bigint *a, const Bigint *b, bool type);

Bigint *bigint_div(const Bigint *a, const Bigint *b);

Bigint *bigint_divi(const Bigint *a, const int b);

Bigint *bigint_mod(const Bigint *a, const Bigint *b);

#endif // BIG_INT_H