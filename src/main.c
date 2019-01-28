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

	int x = 999999999, y = 12141;
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
		printf("1001 - 1001 = ");
		Bigint *c1 = bigint_constructorstr("1001");
		Bigint *d1 = bigint_substr(c1, "1001");
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
#endif
}

void test()
{
	printf("Rozpoczynam potęzne testowanie.\n");
	test_print();
	test_copy();
	test_conversions();
	test_add();
	test_compare();
	printf("Poteżne testowanie zakończone sukcesem.\n");
}
