#include "ft_printf.h"

int	ft_pct(va_list args)
{
	(void)args;
	return (ft_putchar('%'));
}

int	ft_chr(va_list args)
{
	char	c;

	c = (char) va_arg(args, int);
	return (ft_putchar(c));
}

int	ft_str(va_list args)
{
	char	*str;
	int		ret;

	str = va_arg(args, char *);
	ret = 0;
	if (!str)
		return (write(1, "(null)", 6), 6);
	while (*str)
		ret += ft_putchar(*str++);
	return (ret);
}

int	ft_nbr(va_list args)
{
	int	nb;
	int	*ret;
	int	init;

	init = 0;
	ret = &init;
	nb = va_arg(args, int);
	ft_putnbrbase(nb, 10, "0123456789", ret);
	return (*ret);
}
