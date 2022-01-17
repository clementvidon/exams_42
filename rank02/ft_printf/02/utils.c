#include "ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_putnbrbase(long nb, long baselen, char *base, int *ret)
{
	if (nb < 0)
	{
		nb = -nb;
		*ret += ft_putchar('-');
	}
	if (nb >= baselen)
		ft_putnbrbase(nb / baselen, baselen, base, ret);
	*ret += ft_putchar(base[nb % baselen]);
}

void	ft_putnbrbase_ptr(unsigned long nb, int baselen, char *base, int *ret)
{
	if (nb >= (unsigned long)baselen)
		ft_putnbrbase_ptr(nb / (unsigned long)baselen, baselen, base, ret);
	*ret += ft_putchar(base[nb % (unsigned long)baselen]);
}
