#include "ft_printf.h"

int ft_pct(va_list args)
{
	(void)args;
	return (ft_putchar('%'));
}

int ft_chr(va_list args)
{
	char	c;

	c = (char) va_arg(args, int);
	return (ft_putchar(c));
}

int ft_str(va_list args)
{
	int		ret;
	char	*str;

	ret = 0;
	str = va_arg(args, char *);
	if (!str)
		return (write(1, "(null)", 6), 6);
	while (*str)
		ret += ft_putchar(*str++);
	return (ret);
}

int ft_nbr(va_list args)
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

int ft_uns(va_list args)
{
	unsigned int	nb;
	int				*ret;
	int				init;

	init = 0;
	ret = &init;
	nb = va_arg(args, unsigned int);
	ft_putnbrbase(nb, 10, "0123456789", ret);
	return (*ret);
}

int ft_hex(va_list args)
{
	unsigned int	nb;
	int				*ret;
	int				init;

	init = 0;
	ret = &init;
	nb = va_arg(args, unsigned int);
	ft_putnbrbase(nb, 16, "0123456789abcdef", ret);
	return (*ret);
}

int ft_ptr(va_list args)
{
	unsigned long	nb;
	int				*ret;
	int				init;

	init = 2;
	ret = &init;
	nb = va_arg(args, unsigned long);
	write(1, "0x", 2);
	ft_putnbrbaseptr(nb, 16, "0123456789abcdef", ret);
	return (*ret);
	(void)args;
	return (0);
}

