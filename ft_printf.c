/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 00:25:27 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/15 21:53:23 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_helper(char c, va_list *list)
{
	if (c == 'c')
		return (ft_putchar(va_arg(*list, int)));
	else if (c == 's')
		return (ft_putstr(va_arg(*list, char *)));
	else if (c == 'p')
		return (ft_putptr(va_arg(*list, unsigned long)));
	else if (c == 'd' || c == 'i')
		return (ft_putnbr(va_arg(*list, int)));
	else if (c == 'u')
		return (ft_putunbr(va_arg(*list, unsigned int)));
	else if (c == 'x' || c == 'X')
		return (ft_puthex(va_arg(*list, unsigned int), c));
	else if (c == '%')
		return (ft_putchar(c));
	return (-1);
}

static int	ft_process(const char *str, int *i, va_list *list)
{
	int	check;

	if (str[*i] == '%')
	{
		(*i)++;
		check = ft_helper(str[*i], list);
	}
	else
		check = ft_putchar(str[*i]);
	return (check);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		rtrn;
	int		check;
	int		i;

	if (!str)
		return (-1);
	i = 0;
	rtrn = 0;
	va_start(list, str);
	while (str[i])
	{
		check = ft_process(str, &i, &list);
		if (check < 0)
		{
			va_end(list);
			return (-1);
		}
		rtrn += check;
		i++;
	}
	va_end(list);
	return (rtrn);
}
