*This project has been created as part of the 42 curriculum by sbouadai.*

# ft_printf

## Description

`ft_printf` is a recode of the C standard library function `printf`. The goal of the project is to build a static library, `libftprintf.a`, that exposes a function with the same prototype and the same behavior as the original for a defined set of conversions:

```c
int	ft_printf(const char *format, ...);
```

It returns the number of characters printed, like `printf`, and only uses `write` for output.

The project teaches how variadic functions work in C (`<stdarg.h>`), how to convert numbers to text in different bases without the standard library, and how to split a task into small functions that respect the 42 Norm.

### Supported conversions

| Specifier | Output |
|---|---|
| `%c` | a single character |
| `%s` | a string (`(null)` if the pointer is `NULL`) |
| `%p` | a pointer in hexadecimal, prefixed with `0x` (`(nil)` if `NULL`) |
| `%d` | a signed decimal integer |
| `%i` | a signed decimal integer |
| `%u` | an unsigned decimal integer |
| `%x` | an unsigned hexadecimal integer, lowercase |
| `%X` | an unsigned hexadecimal integer, uppercase |
| `%%` | a literal percent sign |

## Instructions

### Compilation

The library is built with `cc` and the flags `-Wall -Wextra -Werror`.

```sh
make        # builds libftprintf.a
make clean  # removes the object files
make fclean # removes the object files and libftprintf.a
make re     # fclean followed by make
```

### Usage

Include the header in your code, then link your program against the library:

```c
#include "ft_printf.h"

int	main(void)
{
	int	len;

	len = ft_printf("Hello %s, you are %d years old\n", "world", 42);
	ft_printf("%d characters printed\n", len);
	return (0);
}
```

```sh
cc -Wall -Wextra -Werror main.c libftprintf.a -o demo
./demo
```

Rebuild your test program every time the library changes, otherwise an old binary may be linked against an old copy of the code.

### Project structure

```
.
├── Makefile
├── ft_printf.h      prototypes and includes
├── ft_printf.c      ft_printf and the conversion dispatcher
├── ft_print_char.c  ft_putchar, ft_putstr
├── ft_print_nbr.c   ft_putnbr, ft_putunbr
└── ft_print_hex.c   ft_puthex and the base helper
└── ft_print_ptr.c   ft_putptr
```

## Algorithm and design

### Main loop

`ft_printf` walks through the format string one character at a time:

1. A normal character is written as is.
2. A `%` means the next character is a specifier. The dispatcher reads the matching argument and calls the right print function.
3. Every print function returns the number of characters it wrote. `ft_printf` adds these values to a running total, and returns it at the end.
4. If a write fails or the format is invalid, the function stops and returns `-1`.

### Reading the arguments

The arguments come from a `va_list`, initialized with `va_start`, read with `va_arg` and closed with `va_end`. The type passed to `va_arg` must match the type the caller passed, because C stores no type information for variadic arguments:

| Specifier | Type read with `va_arg` |
|---|---|
| `%c` | `int` (a `char` is promoted to `int`) |
| `%s` | `char *` |
| `%d`, `%i` | `int` |
| `%u`, `%x`, `%X` | `unsigned int` |
| `%p` | `unsigned long` (a pointer is 8 bytes on a 64-bit system) |

The `va_list` is passed by pointer to the helper functions, so that every argument consumed in a helper also advances the list in the caller.

### Edge cases

- **`INT_MIN`**: for `%d` and `%i`, the value is first copied into a `long`, so negating it does not overflow.
- **Negative values with `%x`, `%X` and `%u`**: the argument is read as `unsigned int`, so the bits are reinterpreted and no sign is printed.
- **`%p`**: the value is read as `unsigned long` so that the whole 64-bit address is kept. A null pointer prints `(nil)`.
- **`%s` with `NULL`**: prints `(null)`.
- **Trailing `%`**: a format ending with a single `%` stops the function and returns `-1`.


## Resources

- `man 3 printf`, `man 3 stdarg`, `man 2 write`
- [Variadic function in C](https://www.geeksforgeeks.org/c/variadic-functions-in-c/)
- [A Youtube video about variadic function](https://youtu.be/7Sph8JlRo0g?si=YRSKL0VdwsLG83fq)

### Use of AI

An AI assistant was used as a tutor during this project: to explain how variadic functions and `va_list` work internally, and to generate a test program comparing `ft_printf` with `printf`. The code of the library itself was written by me, and every explanation and suggestion was checked by compiling and testing it.