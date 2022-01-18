/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 10:12:04 by cvidon            #+#    #+#             */
/*   Updated: 2021/12/07 16:18:05 by cvidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

# include <stdio.h>

void	ft_putnbrbase(long n, int baselen, char *base, int *len);
void	ft_putnbrbase_ptr(unsigned long n, int baselen, char *base, int *len);
int		ft_putchar(char c);
int		ft_putstr(char *s);

int		ft_chr(va_list args);
int		ft_str(va_list args);
int		ft_ptr(va_list args);
int		ft_nbr(va_list args);

int		ft_uni(va_list args);
int		ft_hx1(va_list args);
int		ft_hx2(va_list args);
int		ft_pct(va_list args);

int		ft_printf(const char *fmt, ...);

#endif
