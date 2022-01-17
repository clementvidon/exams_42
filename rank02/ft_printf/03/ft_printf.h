#ifndef FT_PRINTF
# define FT_PRINTF

#include <unistd.h>
#include <stdarg.h>

#include <stdio.h>
#include <stdlib.h>

int 	ft_printf(const char *fmt, ...);

int 	ft_pct(va_list args);
int 	ft_chr(va_list args);
int 	ft_str(va_list args);
int 	ft_nbr(va_list args);
int 	ft_uns(va_list args);
int 	ft_hex(va_list args);
int 	ft_ptr(va_list args);

int		ft_putchar(char c);
void	ft_putnbrbase(long nb, int baselen, char *base, int *ret);
void	ft_putnbrbaseptr(unsigned long nb, int baselen, char *base, int *ret);

#endif
