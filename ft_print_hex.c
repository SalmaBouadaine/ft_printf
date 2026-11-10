/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouadai <sbouadai@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 14:46:30 by sbouadai          #+#    #+#             */
/*   Updated: 2026/11/10 16:16:15 by sbouadai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbrbase(unsigned long nbr, char * base)
{
	int	count;
	char		c;

	count = 0;
	if (nbr >= 16)
		count += ft_putnbrbase(nbr / 16, base);
	c = base[nbr % 16];
	count += write(1, &c, 1);
	return (count);
}

int	ft_puthex(unsigned long n, char c)
{
	if (c == 'x')
		return (ft_putnbrbase(n, "0123456789abcdef"));
	else
		return (ft_putnbrbase(n, "0123456789ABCDEF"));
}