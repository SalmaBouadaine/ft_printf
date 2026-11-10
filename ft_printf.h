#ifndef FT_PRINTF
#define FT_PRINTF

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_putchar(char c);
int	ft_putstr(char *s);
int	ft_putnbr(int n);
int	ft_putunbr(unsigned int n);
int	ft_puthex(unsigned long n, char c);
int	ft_putptr(unsigned long n);
int	ft_printf(const char *str, ...);


#endif