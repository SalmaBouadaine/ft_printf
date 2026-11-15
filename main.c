#include <stdio.h>
#include <limits.h>

/* Reference sheet: runs ONLY the real printf, no ft_printf needed.
   Each line shows: the call, the exact output between [ ], the return value.
   Compile: cc ref_printf.c -o ref && ./ref
   Save the output to read it calmly: ./ref > ref.txt */

#pragma GCC diagnostic ignored "-Wformat"
#pragma GCC diagnostic ignored "-Wformat-extra-args"
#pragma GCC diagnostic ignored "-Wformat-zero-length"
#pragma GCC diagnostic ignored "-Wformat-security"

#define TEST(...) do { \
	int	r; \
	printf("%-34s -> [", #__VA_ARGS__); \
	r = printf(__VA_ARGS__); \
	printf("] ret=%d\n", r); \
} while (0)

static void	section(const char *name, int undef)
{
	printf("\n===== %s%s =====\n", name,
		undef ? " (undefined by the standard, glibc behavior)" : "");
}

int	main(void)
{
	int		x = 42;
	char	*str = "hello";

	(void)x;
	(void)str;
	section("WIDTH", 0);
	TEST("%5d", 42);
	TEST("%5d", -42);
	TEST("%1d", 42);
	TEST("%2d", 12345);
	TEST("%10d", INT_MIN);
	TEST("%10d", INT_MAX);
	TEST("%5d", 0);
	TEST("%5i", 42);
	TEST("%5u", 42);
	TEST("%10u", UINT_MAX);
	TEST("%5c", 'a');
	TEST("%1c", 'a');
	TEST("%5s", "ab");
	TEST("%2s", "abcdef");
	TEST("%20s", "hello");
	TEST("%5s", "");
	TEST("%10s", (char *)NULL);
	TEST("%3s", (char *)NULL);
	TEST("%8x", 255);
	TEST("%8X", 255);
	TEST("%8x", 0);
	TEST("%2x", 4096);
	TEST("%5p", &x);
	TEST("%25p", &x);
	TEST("%10p", (void *)NULL);
	TEST("%3p", (void *)NULL);
	TEST("%50d", 42);
	TEST("%100s", "far");

	/* ---------------------------------------------------------------- */
	section("MINUS (left justify)", 0);
	TEST("%-5d|", 42);
	TEST("%-5d|", -42);
	TEST("%-1d|", 42);
	TEST("%-10d|", INT_MIN);
	TEST("%-5i|", 7);
	TEST("%-5u|", 42);
	TEST("%-12u|", UINT_MAX);
	TEST("%-5c|", 'a');
	TEST("%-5s|", "ab");
	TEST("%-10s|", "hello");
	TEST("%-2s|", "hello");
	TEST("%-10s|", (char *)NULL);
	TEST("%-8x|", 255);
	TEST("%-8X|", 255);
	TEST("%-8x|", 0);
	TEST("%-20p|", &x);
	TEST("%-10p|", (void *)NULL);
	TEST("%-5d|%-5d|", 1, 2);

	/* ---------------------------------------------------------------- */
	section("PRECISION: integers", 0);
	TEST("%.0d", 0);
	TEST("%.0d", 1);
	TEST("%.d", 0);
	TEST("%.d", 5);
	TEST("%.1d", 0);
	TEST("%.5d", 42);
	TEST("%.5d", -42);
	TEST("%.1d", 42);
	TEST("%.2d", 12345);
	TEST("%.10d", INT_MIN);
	TEST("%.10d", INT_MAX);
	TEST("%.5i", 7);
	TEST("%.0u", 0);
	TEST("%.u", 0);
	TEST("%.5u", 42);
	TEST("%.12u", UINT_MAX);
	TEST("%.5x", 255);
	TEST("%.5X", 255);
	TEST("%.0x", 0);
	TEST("%.x", 0);
	TEST("%.1x", 0);
	TEST("%.8x", 0xabc);
	TEST("%.3x", 0xabcdef);

	/* ---------------------------------------------------------------- */
	section("PRECISION: strings", 0);
	TEST("%.0s", "hello");
	TEST("%.s", "hello");
	TEST("%.3s", "abcdef");
	TEST("%.5s", "abcde");
	TEST("%.10s", "abc");
	TEST("%.1s", "abc");
	TEST("%.3s", "");
	TEST("%.s", "");
	TEST("%.0s", (char *)NULL);
	TEST("%.s", (char *)NULL);
	TEST("%.3s", (char *)NULL);
	TEST("%.5s", (char *)NULL);
	TEST("%.6s", (char *)NULL);
	TEST("%.10s", (char *)NULL);

	/* ---------------------------------------------------------------- */
	section("ZERO flag", 0);
	TEST("%05d", 42);
	TEST("%05d", -42);
	TEST("%0d", 42);
	TEST("%01d", 42);
	TEST("%02d", 12345);
	TEST("%010d", INT_MIN);
	TEST("%010d", INT_MAX);
	TEST("%05d", 0);
	TEST("%05i", -7);
	TEST("%05u", 42);
	TEST("%012u", UINT_MAX);
	TEST("%08x", 255);
	TEST("%08X", 255);
	TEST("%08x", 0);
	TEST("%08x", -1);
	TEST("%00005d", 42);

	/* ---------------------------------------------------------------- */
	section("WIDTH + PRECISION", 0);
	TEST("%5.3d|", 42);
	TEST("%8.5d|", 42);
	TEST("%8.5d|", -42);
	TEST("%3.5d|", 42);
	TEST("%3.5d|", -42);
	TEST("%10.0d|", 0);
	TEST("%10.d|", 0);
	TEST("%10.3d|", 0);
	TEST("%10.5u|", 42);
	TEST("%10.5x|", 255);
	TEST("%10.5X|", 255);
	TEST("%10.0x|", 0);
	TEST("%10.5s|", "hello world");
	TEST("%10.3s|", "hello");
	TEST("%3.5s|", "hello");
	TEST("%10.0s|", "hello");
	TEST("%10.3s|", (char *)NULL);
	TEST("%10.6s|", (char *)NULL);

	/* ---------------------------------------------------------------- */
	section("MINUS + PRECISION / WIDTH", 0);
	TEST("%-5.3d|", 42);
	TEST("%-8.5d|", -42);
	TEST("%-3.5d|", 42);
	TEST("%-10.0d|", 0);
	TEST("%-10.5u|", 42);
	TEST("%-10.5x|", 255);
	TEST("%-10.3s|", "hello");
	TEST("%-10.0s|", "hello");
	TEST("%-10.3s|", (char *)NULL);

	/* ---------------------------------------------------------------- */
	section("ZERO + other flags", 0);
	TEST("%-05d|", 42);
	TEST("%-05d|", -42);
	TEST("%0-5d|", 42);
	TEST("%05.3d|", 42);
	TEST("%05.3d|", -42);
	TEST("%08.5d|", 42);
	TEST("%08.5d|", -42);
	TEST("%05.0d|", 0);
	TEST("%08.5u|", 42);
	TEST("%08.5x|", 255);
	TEST("%-08x|", 255);
	TEST("%-08.5x|", 255);

	/* ---------------------------------------------------------------- */
	section("HASH flag", 0);
	TEST("%#x", 255);
	TEST("%#X", 255);
	TEST("%#x", 0);
	TEST("%#X", 0);
	TEST("%#x", 1);
	TEST("%#x", UINT_MAX);
	TEST("%#X", UINT_MAX);
	TEST("%#x", -1);
	TEST("%#10x|", 255);
	TEST("%#10X|", 255);
	TEST("%#10x|", 0);
	TEST("%#-10x|", 255);
	TEST("%#-10X|", 255);
	TEST("%#-10x|", 0);
	TEST("%#010x|", 255);
	TEST("%#010X|", 255);
	TEST("%#010x|", 0);
	TEST("%#.5x|", 255);
	TEST("%#.5X|", 255);
	TEST("%#.0x|", 0);
	TEST("%#.0x|", 255);
	TEST("%#10.5x|", 255);
	TEST("%#10.5X|", 255);
	TEST("%#-10.5x|", 255);
	TEST("%#010.5x|", 255);
	TEST("%#3x|", 255);
	TEST("%#4x|", 255);
	TEST("%#5x|", 255);
	TEST("%#08x|", 0);

	/* ---------------------------------------------------------------- */
	section("PLUS flag", 0);
	TEST("%+d", 42);
	TEST("%+d", -42);
	TEST("%+d", 0);
	TEST("%+i", 42);
	TEST("%+d", INT_MAX);
	TEST("%+d", INT_MIN);
	TEST("%+5d|", 42);
	TEST("%+5d|", -42);
	TEST("%+1d|", 42);
	TEST("%+-5d|", 42);
	TEST("%+-5d|", -42);
	TEST("%+05d|", 42);
	TEST("%+05d|", -42);
	TEST("%+05d|", 0);
	TEST("%+.5d|", 42);
	TEST("%+.5d|", -42);
	TEST("%+.0d|", 0);
	TEST("%+.d|", 0);
	TEST("%+10.5d|", 42);
	TEST("%+10.5d|", -42);
	TEST("%+-10.5d|", 42);
	TEST("%+010.5d|", 42);
	TEST("%+3.5d|", 42);

	/* ---------------------------------------------------------------- */
	section("SPACE flag", 0);
	TEST("% d", 42);
	TEST("% d", -42);
	TEST("% d", 0);
	TEST("% i", 42);
	TEST("% d", INT_MAX);
	TEST("% d", INT_MIN);
	TEST("% 5d|", 42);
	TEST("% 5d|", -42);
	TEST("% 1d|", 42);
	TEST("% -5d|", 42);
	TEST("% -5d|", -42);
	TEST("% 05d|", 42);
	TEST("% 05d|", -42);
	TEST("% 05d|", 0);
	TEST("% .5d|", 42);
	TEST("% .5d|", -42);
	TEST("% .0d|", 0);
	TEST("% .d|", 0);
	TEST("% 10.5d|", 42);
	TEST("% 10.5d|", -42);
	TEST("% -10.5d|", 42);
	TEST("% 010.5d|", 42);

	/* ---------------------------------------------------------------- */
	section("PLUS + SPACE (plus wins)", 0);
	TEST("% +d", 42);
	TEST("%+ d", 42);
	TEST("% +d", -42);
	TEST("%+ d", -42);
	TEST("% +d", 0);
	TEST("% +5d|", 42);
	TEST("%+ 5d|", 42);
	TEST("% +-5d|", 42);
	TEST("% +05d|", 42);
	TEST("% +.5d|", 42);

	/* ---------------------------------------------------------------- */
	section("ALL FLAGS together (integers)", 0);
	TEST("%-+5d|", 42);
	TEST("%0+5d|", 42);
	TEST("%-+ 5d|", 42);
	TEST("%-+ 010d|", 42);
	TEST("%-+ 10.5d|", 42);
	TEST("%+ 010.5d|", -42);
	TEST("%-+ 10.5d|", -42);
	TEST("%+.0d|", 0);
	TEST("% .0d|", 0);
	TEST("%+10.0d|", 0);
	TEST("%-+10.0d|", 0);

	/* ---------------------------------------------------------------- */
	section("REPEATED flags and big widths", 0);
	TEST("%--5d|", 42);
	TEST("%++d", 42);
	TEST("%  d", 42);
	TEST("%###x", 255);
	TEST("%0-0-5d|", 42);
	TEST("%-+-+5d|", 42);
	TEST("%100d|", 42);
	TEST("%-100d|", 42);
	TEST("%.100d|", 42);
	TEST("%100.50d|", 42);
	TEST("%100.50s|", "text");

	/* ---------------------------------------------------------------- */
	section("MIXED conversions in one call", 0);
	TEST("%-5d|%05d|%+d|% d|%#x|%.3s", 1, 2, 3, 4, 255, "abcdef");
	TEST("%5c|%-5c|%5s|%-5s|", 'a', 'b', "cd", "ef");
	TEST("%10.3d|%-10.3d|%010d|%+10d|", 5, 5, 5, 5);
	TEST("%#x %#X %#o", 255, 255, 8);
	TEST("%5%|");
	TEST("%-5%|");
	TEST("%c %s %d %i %u %x %X %p %%", 'z', "m", -5, 6, 7u, 255, 255, &x);
	TEST("%+d %+d %+d", 1, -1, 0);
	TEST("%.3s%.3s%.3s", "abcdef", "ghijkl", "mnopqr");
	TEST("%20s%-20s|", str, str);
	TEST("%s%s%s", "a", (char *)NULL, "c");

	/* ---------------------------------------------------------------- */
	/* Behaviors the C standard leaves undefined. Do not panic on "??". */
	/* Compare with glibc, but evaluators rarely test these.            */
	section("UNDEFINED behavior (informational only)", 1);
	TEST("%#d", 42);
	TEST("%#u", 42);
	TEST("%#s", "hello");
	TEST("%#c", 'a');
	TEST("%#p", &x);
	TEST("%+u", 42);
	TEST("%+x", 255);
	TEST("%+s", "hello");
	TEST("%+c", 'a');
	TEST("%+p", &x);
	TEST("% u", 42);
	TEST("% x", 255);
	TEST("% s", "hello");
	TEST("% c", 'a');
	TEST("% p", &x);
	TEST("%0s", "hello");
	TEST("%05s", "hello");
	TEST("%05c", 'a');
	TEST("%05p", &x);
	TEST("%010p", (void *)NULL);
	TEST("%05%");
	TEST("%.3c", 'a');
	TEST("%.5p", &x);
	TEST("%.0p", (void *)NULL);
	TEST("%.3%");
	TEST("%-05s|", "hi");

	return (0);
}