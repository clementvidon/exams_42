#include "ft_printf.h"

int	ft_uni(va_list args)
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

int	ft_hx1(va_list args)
{
	unsigned int	nb; 	// NOT LONG
	int				*ret;
	int				init;

	init = 0;
	ret = &init;
	nb = va_arg(args, unsigned int);
	ft_putnbrbase(nb, 16, "0123456789abcdef", ret);
	return (*ret);
}

int	ft_hx2(va_list args)
{
	unsigned int	nb;		// NOT LONG
	int				*ret;
	int				init;

	init = 0;
	ret = &init;
	nb = va_arg(args, unsigned int);
	ft_putnbrbase(nb, 16, "0123456789ABCDEF", ret);
	return (*ret);
}

int	ft_ptr(va_list args)
{
	unsigned long	nb;
	int				*ret;
	int				init;

	init = 0;
	ret = &init;
	*ret += 2;
	write (1, "0x", 2);
	nb = va_arg(args, unsigned long);
	ft_putnbrbase_ptr(nb, 16, "0123456789abcdef", ret);
	return (*ret);
}
