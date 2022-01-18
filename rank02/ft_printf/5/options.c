#include "ft_printf.h"

int	ft_pct(va_list args)
{
	(void)args;
	return ((int)write(1, "%", 1));
}

int	ft_chr(va_list args)
{
	char	c;

	c = (char) va_arg(args, int);
	return ((int)write(1, &c, 1));
}

int	ft_str(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		return ((int)write(1, "(null)", 6));
	return ((int)write(1, str, ft_strlen(str)));
}

/* ptr better than init for var name */

int	ft_nbr(va_list args)
{
	int	ret;
	int	*ptr;
	int	nb;

	ret = 0;
	ptr = &ret;
	nb = va_arg(args, int);
	ft_putnbr_base(nb, 10, "0123456789", &ret);
	return (*ptr);
}


int	ft_uns(va_list args)
{
	int	ret;
	int	*ptr;
	unsigned int	nb;

	ret = 0;
	ptr = &ret;
	nb = (unsigned int) va_arg(args, int);
	ft_putnbr_base(nb, 10, "0123456789", &ret);
	return (*ptr);
}


int	ft_hex(va_list args)
{
	int				ret;
	int				*ptr;
	unsigned int	nb;

	ret = 0;
	ptr = &ret;
	nb = (unsigned int) va_arg(args, int);
	ft_putnbr_base(nb, 16, "0123456789abcdef", &ret);
	return (*ptr);
}


int	ft_ptr(va_list args)
{
	int				ret;
	int				*ptr;
	unsigned long	nb;

	ret = (int)write(1, "0x", 2);
	ptr = &ret;
	nb = (unsigned long) va_arg(args, long);
	ft_putnbr_baseptr(nb, 16, "0123456789abcdef", &ret);
	return (*ptr);
}

