////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "bigint.h"
#include <stdio.h>
#include "parser.h"

void test();
int main(int argc, char const *argv[])
{
	test();
	return 0;
}

void test()
{
	char *s = malloc(1000);
	while (true)
	{
		printf("Exit(0) or Calculate expression(1)\n");
		int x;
		scanf("%d", &x);
		if (x == 0)
			break;
		printf("Type expresion:\n");
		scanf(" %[^\n]", s);

		if (pareser_check(s) == 0)
		{
			printf("Wrong expresion.\n");
			continue;
		}

		Bigint *a = parse(s);
		printf("=");
		bigint_println(a);
	}
}
