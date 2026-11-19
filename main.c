#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

/* Runs printf and ft_printf with the same args, compares return values.
   Compare the printed output by eye: lines starting with "std" and "ft". */
#define TEST(...) do { \
	int r1, r2; \
	printf("std: ["); fflush(stdout); \
	r1 = printf(__VA_ARGS__); \
	printf("] ret=%d\n", r1); \
	printf("ft : ["); fflush(stdout); \
	r2 = ft_printf(__VA_ARGS__); \
	printf("] ret=%d  %s\n\n", r2, r1 == r2 ? "OK" : "KO <-- return differs"); \
} while (0)

int	main(void)
{
	int	x = 42;

	/* %c */
	TEST("%c", 'A');
	TEST("%c%c%c", 'a', ' ', 'z');
	TEST("%c", 0);

	/* %s */
	TEST("%s", "hello world");
	TEST("%s", "");
	TEST("%s", (char *)NULL);

	/* %p (NULL prints "(nil)" on Linux, "0x0" on macOS) */
	TEST("%p", &x);
	TEST("%p", (void *)0);
	TEST("%p", (void *)-1);

	/* %d / %i */
	TEST("%d", 0);
	TEST("%d", -42);
	TEST("%d", INT_MAX);
	TEST("%d", INT_MIN);
	TEST("%i", 123456);

	/* %u */
	TEST("%u", 0);
	TEST("%u", UINT_MAX);
	TEST("%u", -1);

	/* %x / %X */
	TEST("%x", 0);
	TEST("%x", 255);
	TEST("%X", 255);
	TEST("%x", UINT_MAX);
	TEST("%X", 3735928559u);

	/* %% */
	TEST("%%");
	TEST("100%%");
	TEST("%%%c%%", 'x');

	/* mixed */
	TEST("Hello %s, you are %d years old (%x) %c %%", "Bob", 25, 25, '!');
	TEST("%s %s %s", "a", "b", "c");
	TEST("no format at all");
	TEST("");

	return (0);
}
