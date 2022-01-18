#include "ft_printf.h"

static int ft_parse(int (*options[7])(va_list), const char *fmt, va_list args)
{
	int	ret;
	int	id;

	ret = 0;
	while(*fmt)
	{
		if (*fmt != '%')
			ret += ft_putchar(*fmt);
		else
		{
			fmt++;
			id = 0 * (*fmt == '%')
				+ 1 * (*fmt == 'c')
				+ 2 * (*fmt == 's')
				+ 3 * (*fmt == 'd' | *fmt == 'i')
				+ 4 * (*fmt == 'u')
				+ 5 * (*fmt == 'x')
				+ 6 * (*fmt == 'p')
				;
			ret += options[id](args);
		}
		fmt++;
	}
	return (ret);
}

int ft_printf(const char *fmt, ...)
{
	va_list args;
	int		(*options[7])(va_list);
	int		ret;

	ret = 0;
	options[0] = ft_pct;
	options[1] = ft_chr;
	options[2] = ft_str;
	options[3] = ft_nbr;
	options[4] = ft_uns;
	options[5] = ft_hex;
	options[6] = ft_ptr;
	va_start(args, fmt);
	ret = ft_parse(options, fmt, args);
	va_end(args);
	return (ret);
}

