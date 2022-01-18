#include "ft_printf.h"

int	ft_parse(int (*options[7])(va_list), const char *fmt, va_list args)
{
	int	ret;
	int	id;

	ret = 0;
	while (*fmt)
	{
		if (*fmt != '%')
			ret += write(1, fmt++, 1);
		else
		{
			fmt++;
			id = 0 * (*fmt == '%')
				+ 1 * (*fmt == 'c')
				+ 2 * (*fmt == 's')
				+ 3 * (*fmt == 'i' | *fmt == 'd')
				+ 4 * (*fmt == 'u')
				+ 5 * (*fmt == 'x')
				+ 6 * (*fmt == 'p')
				;
			ret += options[id](args);
			fmt++;
		}
	}
	return (ret);
}

/* Remove useless 'ret = 0' init */

int	ft_printf(const char *fmt, ...)
{
	int		(*options[7])(va_list);
	va_list	args;
	int		ret;

	/* Init */
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
