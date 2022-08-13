#include "ft_printf.h"

/* Int-putchar is useless because write has a ret value */

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putnbr_base(long nb, int baselen, char *base, int *ret)
{
	if (nb < 0)
	{
		nb = -nb;
		*ret += write(1, "-", 1);
	}
	if (nb >= (long)baselen)
		ft_putnbr_base(nb / (long)baselen, baselen, base, ret);
	*ret += (int)write(1, &base[nb % (long)baselen], 1);
}

void	ft_putnbr_baseptr(unsigned long nb, int baselen, char *base, int *ret)
{
	if (nb >= (unsigned long)baselen)
		ft_putnbr_baseptr(nb / (unsigned long)baselen, baselen, base, ret);
	*ret += (int)write(1, &base[nb % (unsigned long)baselen], 1);
}
