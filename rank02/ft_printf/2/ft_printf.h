#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* Includes */
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

/* Core */
int		ft_printf(const char *fmt, ...);
/* Options */
int		ft_pct(va_list args);
int		ft_chr(va_list args);
int		ft_str(va_list args);
int		ft_nbr(va_list args);
int		ft_uni(va_list args);
int		ft_hx1(va_list args);
int		ft_hx2(va_list args);
int		ft_ptr(va_list args);
/* Utils */
int		ft_putchar(char c);
void	ft_putnbrbase(long nb, long baselen, char *base, int *ret);
void	ft_putnbrbase_ptr(unsigned long nb, int baselen, char *base, int *ret);

#endif
