#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* Prod */
#include <stdarg.h>
#include <unistd.h>

/* Dev */
#include <stdio.h>

/* utils.c */
size_t	ft_strlen(char *str);
void	ft_putnbr_base(long nb, int baselen, char *base, int *ret);
void	ft_putnbr_baseptr(unsigned long nb, int baselen, char *base, int *ret);
/* ft_printf.c */
int	ft_printf(const char *fmt, ...);
/* options.c */
int	ft_pct(va_list args);
int	ft_chr(va_list args);
int	ft_str(va_list args);
int	ft_nbr(va_list args);
int	ft_uns(va_list args);
int	ft_hex(va_list args);
int	ft_ptr(va_list args);

#endif
