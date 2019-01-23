////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "bigInt.h"
#include <stdio.h>

void test();
int main(int argc, char const *argv[])
{
	test();
	return 0;
}

#if 1
#define TEST_PRINT
#endif

#if 1
#define TEST_COPY
#endif

#if 1
#define TEST_CONVERSIONS
#endif

void test_print()
{
#if defined(TEST_PRINT)
	printf("Rozpoczynam testowanie wypisywania.\n");
	printf("val : 0\n");
	BigInt *aa = bigInt_constructor();
	bigInt_println(aa);

	int val1 = 112314;
	printf("val : \n%d\n", val1);
	bigInt_assigni(aa, val1);
	bigInt_println(aa);

	long long val2 = 112311232244ll;
	printf("val : \n%ld\n", val2);
	bigInt_assignll(aa, val2);
	bigInt_println(aa);

	long long val3 = 11200000002244ll;
	printf("val : \n%ld\n", val3);
	bigInt_assignll(aa, val3);
	bigInt_println(aa);

	printf("Testowanie wypisywania zakończone sukcesem.\n");
#endif // TEST_PRINT
}

void test_copy()
{
#if defined(TEST_COPY)
	printf("Rozpoczynam testowanie kopiowania.\n");

	BigInt *a = bigInt_constructor();
	bigInt_println(a);
	BigInt *b = bigInt_copy(a);
	bigInt_println(b);

	BigInt *c = bigInt_constructori(123123);
	bigInt_println(c);
	BigInt *d = bigInt_copy(c);
	bigInt_println(d);

	printf("Testowanie kopiowania zakończone sukcesem.\n");
#endif // TEST_COPY
}

void test_conversions()
{
#if defined(TEST_CONVERSIONS)
	printf("Rozpoczynam testowanie zamian.\n");
	BigInt *a = bigInt_constructor();
	bigInt_println(a);
	printf("%s\n", bigInt_tostring(a));
	BigInt *b = bigInt_constructorll(123456789123455ll);
	bigInt_println(b);
	printf("%s\n", bigInt_tostring(b));
	BigInt *c = bigInt_constructorll(-12340000010455ll);
	bigInt_println(c);
	printf("%s\n", bigInt_tostring(c));

	const char *s = "123124";
	printf("%s\n", s);
	BigInt *d = bigInt_constructorstr(s);
	bigInt_println(d);

	const char *ss = "-21312312412410000123124";
	printf("%s\n", ss);
	BigInt *dd = bigInt_constructorstr(ss);
	bigInt_println(dd);

	printf("Testowanie zamian zakończone sukcesem.\n");
#endif // TEST_CONVERSIONS
}

void test()
{
	printf("Rozpoczynam potęzne testowanie.\n");
	test_print();
	test_copy();
	test_conversions();
	printf("Poteżne testowanie zakończone sukcesem.\n");
}
