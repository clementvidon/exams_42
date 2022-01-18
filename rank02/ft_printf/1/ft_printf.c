/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:11:59 by cvidon            #+#    #+#             */
/*   Updated: 2021/12/07 16:19:16 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	parsing(int (*option[8])(va_list), const char *fmt, va_list args)
{
	int	ret;
	int	id;

	ret = 0;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			ft_putchar(*fmt);
			ret++;
		}
		else
		{
			fmt++;
			id = 0 * (*fmt == '%')
				+ 1 * (*fmt == 'c')
				+ 2 * (*fmt == 's')
				+ 3 * (*fmt == 'i' || *fmt == 'd')
				+ 4 * (*fmt == 'u')
				+ 5 * (*fmt == 'x')
				+ 6 * (*fmt == 'X')
				+ 7 * (*fmt == 'p');
			ret += (*option[id])(args);
		}
		fmt++;
	}
	return (ret);
}

//					   formats, arguments
//						  "%s", str
int	ft_printf(const char *fmt, ...)
{
	int		(*option[8])(va_list); 	// notre liste d'options, prends un 'va_arg' et renvoie un 'int'
	va_list	args; 					// 'args' contiendra tous les arguments
	int		ret; 					// valeur de retour de printf

	/* Init */
	ret = 0;
	option[0] = ft_pct;
	option[1] = ft_chr;
	option[2] = ft_str;
	option[3] = ft_nbr;
	option[4] = ft_uni;
	option[5] = ft_hx1;
	option[6] = ft_hx2;
	option[7] = ft_ptr;

	va_start(args, fmt); 	// START (fmt is the lase non-variadic arg of our func)
	ret = parsing(option, fmt, args);
	va_end(args); 			// END 	(now args is undefined)

	return (ret);
}
