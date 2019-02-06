////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "bigint.h"
#include <stdio.h>

void test();
int main(int argc, char const *argv[])
{
	test();
	return 0;
}

#if 1
#define TEST
#endif

#if 0
#define TEST_PRINT
#endif

#if 0
#define TEST_COPY
#endif

#if 0
#define TEST_CONVERSIONS
#endif

#if 0
#define TEST_ADD
#endif

#if 0
#define TEST_COMPARE
#endif

#if 0
#define TEST_MULT
#endif

#if 0
#define TEST_DIV
#endif

#if 1
#define TEST_MULT_FAST
#endif

void test_print()
{
#if defined(TEST_PRINT)
	printf("Rozpoczynam testowanie wypisywania.\n");
	printf("val : 0\n");
	Bigint *aa = bigint_constructor();
	bigint_println(aa);

	int val1 = 112314;
	printf("val : \n%d\n", val1);
	bigint_assigni(aa, val1);
	bigint_println(aa);

	long long val2 = 112311232244ll;
	printf("val : \n%lld\n", val2);
	bigint_assignll(aa, val2);
	bigint_println(aa);

	long long val3 = 11200000002244ll;
	printf("val : \n%lld\n", val3);
	bigint_assignll(aa, val3);
	bigint_println(aa);

	printf("Testowanie wypisywania zakończone sukcesem.\n");
#endif // TEST_PRINT
}

void test_copy()
{
#if defined(TEST_COPY)
	printf("Rozpoczynam testowanie kopiowania.\n");

	Bigint *a = bigint_constructor();
	bigint_println(a);
	Bigint *b = bigint_copy(a);
	bigint_println(b);

	Bigint *c = bigint_constructori(123123);
	bigint_println(c);
	Bigint *d = bigint_copy(c);
	bigint_println(d);

	printf("Testowanie kopiowania zakończone sukcesem.\n");
#endif // TEST_COPY
}

void test_conversions()
{
#if defined(TEST_CONVERSIONS)
	printf("Rozpoczynam testowanie zamian.\n");
	Bigint *a = bigint_constructor();
	bigint_println(a);
	printf("%s\n", bigint_tostring(a));
	Bigint *b = bigint_constructorll(123456789123455ll);
	bigint_println(b);
	printf("%s\n", bigint_tostring(b));
	Bigint *c = bigint_constructorll(-12340000010455ll);
	bigint_println(c);
	printf("%s\n", bigint_tostring(c));

	const char *s = "123124";
	printf("%s\n", s);
	Bigint *d = bigint_constructorstr(s);
	bigint_println(d);

	const char *ss = "-21312312412410000123124";
	printf("%s\n", ss);
	Bigint *dd = bigint_constructorstr(ss);
	bigint_println(dd);

	printf("Testowanie zamian zakończone sukcesem.\n");
#endif // TEST_CONVERSIONS
}

void test_add()
{
#if defined(TEST_ADD)
	printf("Rozpoczynam testowanie dodawania.\n");

	int x = 1000000000, y = 0;
	printf("%d + %d\n", x, y);
	Bigint *a = bigint_constructori(x);
	Bigint *b = bigint_addi(a, y);
	bigint_println(b);

	long long x1 = -11241214, y1 = -1;
	printf("%lld + %lld\n", x1, y1);
	Bigint *c = bigint_constructorll(x1);
	Bigint *d = bigint_addll(c, y1);
	bigint_println(d);

	long long x2 = -3, y2 = 1;
	printf("%lld + %lld = ", x2, y2);
	Bigint *c1 = bigint_constructorll(x2);
	Bigint *d1 = bigint_addll(c1, y2);
	bigint_println(d1);

	{
		long long x2 = 1, y2 = -3;
		printf("%lld + %lld = ", x2, y2);
		Bigint *c1 = bigint_constructorll(x2);
		Bigint *d1 = bigint_addll(c1, y2);
		bigint_println(d1);
	}

	{
		long long x2 = 1000000000000, y2 = -999999999999;
		printf("%lld + %lld =", x2, y2);
		Bigint *c1 = bigint_constructorll(x2);
		Bigint *d1 = bigint_addll(c1, y2);
		bigint_println(d1);
	}

	{
		long long x2 = 1000000000000, y2 = -999999999999;
		printf("%lld - %lld =", x2, y2);
		Bigint *c1 = bigint_constructorll(x2);
		Bigint *d1 = bigint_subll(c1, y2);
		bigint_println(d1);
	}

	{
		printf("1000000000 + 1000000000 = \n");
		Bigint *c1 = bigint_constructorstr("1000000000");
		Bigint *d1 = bigint_addstr(c1, "1000000000");
		bigint_println(d1);
	}
	printf("Testowanie dodawania zakończone sukcesem.\n");
#endif // TEST_ADD
}

void test_compare()
{
#if defined(TEST_COMPARE)
	printf("Rozpoczynam testowanie porownywania.\n");
	Bigint *a = bigint_constructorstr("12141241");
	Bigint *b = bigint_constructorstr("12121512512512512541411241241");
	bigint_println(a);
	bigint_println(b);
	printf("%d\n", bigint_compare(a, b));
	Bigint *c = bigint_constructori(1241);
	bigint_println(a);
	bigint_println(c);
	printf("%d\n", bigint_compare(a, c));
	printf("Testowanie porownywania zakonczone sukcesem.\n");
#endif // TEST_COMPARE
}

void test_mult()
{
#if defined(TEST_MULT)
	printf("Rozpoczynam testowanie mnozenia.\n");
	{
		Bigint *a = bigint_constructorstr("0");
		Bigint *b = bigint_constructorstr("1000");
		Bigint *c = bigint_mult(a, b);
		bigint_println(c);
	}
	{
		const char *aa = "12", *bb = "-12";
		printf("%s * %s = ", aa, bb);
		Bigint *a = bigint_constructorstr(aa);
		Bigint *b = bigint_constructorstr(bb);
		Bigint *c = bigint_mult(a, b);
		bigint_println(c);
	}

	{
		const char *aa = "2412512512512", *bb = "1251521512";
		printf("%s * %s = ", aa, bb);
		Bigint *a = bigint_constructorstr(aa);
		Bigint *b = bigint_constructorstr(bb);
		Bigint *c = bigint_mult(a, b);
		bigint_println(c);
	}

	{
		const char *aa = "99999", *bb = "999999";
		printf("%s * %s = ", aa, bb);
		Bigint *a = bigint_constructorstr(aa);
		Bigint *b = bigint_constructorstr(bb);
		Bigint *c = bigint_mult(a, b);
		bigint_println(c);
	}

	{
		const char *aa = "99999", *bb = "1000000000";
		printf("%s * %s = ", aa, bb);
		Bigint *a = bigint_constructorstr(aa);
		Bigint *b = bigint_constructorstr(bb);
		Bigint *c = bigint_mult(a, b);
		bigint_println(c);
	}

	printf("Testowanie mnozenia zakonczone sukcesem.\n");
#endif // TEST_MULT
}

void test_div()
{
#if defined(TEST_DIV)
	printf("Rozpoczynam testowanie dzielenia.\n");

	{
		const char *aa = "40000000000010";
		int bb = 2;
		printf("%s / %d = ", aa, bb);
		Bigint *a = bigint_constructorstr(aa);
		Bigint *c = bigint_divi(a, bb);
		bigint_println(c);
	}

	{
		const char *aa = "1000124124142000000000", *bb = "21421412412";
		printf("%s / %s = ", aa, bb);
		Bigint *a = bigint_constructorstr(aa);
		Bigint *b = bigint_constructorstr(bb);
		Bigint *c = bigint_div(a, b);
		bigint_println(c);
	}

	{
		const char *aa = "100000000000102", *bb = "100000000000001";
		printf("%s %% %s = ", aa, bb);
		Bigint *a = bigint_constructorstr(aa);
		Bigint *b = bigint_constructorstr(bb);
		Bigint *c = bigint_mod(a, b);
		bigint_println(c);
	}

	printf("Testowanie dzielenia zakonczone sukcesem.\n");
#endif
}

void test_mult_fast()
{
#if defined(TEST_MULT_FAST)
	printf("Rozpoczynam testowanie szybkiego mnozenia.\n");

	{
		const char *aa = "100", *bb = "2";
		Bigint *a = bigint_constructorstr(aa);
		Bigint *b = bigint_constructorstr(bb);
		printf("%s * %s =\n", aa, bb);
		Bigint *c = bigint_multfast(a, b);
		bigint_println(c);
	}

	{
		const char *aa = "100000", *bb = "124124";
		Bigint *a = bigint_constructorstr(aa);
		Bigint *b = bigint_constructorstr(bb);
		printf("%s * %s =\n", aa, bb);
		Bigint *c = bigint_multfast(a, b);
		bigint_println(c);
	}

	{
		const char *aa = "-100000", *bb = "0";
		Bigint *a = bigint_constructorstr(aa);
		Bigint *b = bigint_constructorstr(bb);
		printf("%s * %s =\n", aa, bb);
		Bigint *c = bigint_multfast(a, b);
		bigint_println(c);
	}

	printf("Testowanie szybkiego mnozenia zakonczone sukcesem.\n");
#endif
}

void test()
{
#if defined(TEST)
	printf("Rozpoczynam potęzne testowanie.\n");
	test_print();
	test_copy();
	test_conversions();
	test_add();
	test_compare();
	test_mult();
	test_div();
	test_mult_fast();
	printf("Poteżne testowanie zakończone sukcesem.\n");
#endif
}
