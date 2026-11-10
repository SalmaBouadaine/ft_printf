/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 00:25:27 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/10 15:21:48 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int ft_helper(char c, va_list list)
{
	if (c == 'c')
		return (ft_putchar(va_arg(list, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(list, char *)));
 	else if (c == 'p')
		return (ft_putptr(va_arg(list,unsigned long)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(list, int)));
	else if (c == 'u')
		return (ft_putunbr(va_arg(list, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthex(va_arg(list, unsigned int), c));
	else if (c == '%')
		return (ft_putchar(c));
	else
		return (-1);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int	rtrn;
	int	check;

	rtrn = 0;
	va_start(list, str);
 	while (*str)
	{
		if (*str == '%' && *(++str))
			check = ft_helper(*str, list);
		else
			check = ft_putchar(*str);
		if (check == -1)
		{
			va_end(list);
			return (check);
		}
		else
			rtrn += check;
		str++;
	}
	va_end(list);
	return (rtrn);
}
