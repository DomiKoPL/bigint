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
	char *s = "(15) - (9 * 5) / 3";
	Bigint *a = parse_expression(s);
	bigint_println(a);
}
