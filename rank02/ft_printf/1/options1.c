/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:12:06 by cvidon            #+#    #+#             */
/*   Updated: 2021/12/03 10:12:07 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pct(va_list args)
{
	(void)args;
	ft_putchar('%');
	return (1);
}

int	ft_chr(va_list args)
{
	char	chr;

	chr = (char)va_arg(args, int);
	return (ft_putchar(chr));
}

int	ft_str(va_list args)
{
	char	*str;

	str = (char *)va_arg(args, char *);
	if (!str)
		return (ft_putstr("(null)"));
	return (ft_putstr(str));
}

int	ft_nbr(va_list args)
{
	long	nb;
	int		*len;
	int		l;

	l = 0;
	len = &l;
	nb = (long)va_arg(args, int);
	ft_putnbrbase(nb, 10, "0123456789", len);
	return (*len);
}
