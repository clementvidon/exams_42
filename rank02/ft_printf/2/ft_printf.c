#include "ft_printf.h"

static int	parser(int (*option[8])(va_list), const char *fmt, va_list args)
{
	int	ret;
	int	id;

	ret = 0;
	while (*fmt)
	{
		if (*fmt != '%')
		{
			ret += ft_putchar(*fmt);
			fmt++;
		}
		else
		{
			fmt++;
			id = 0 * (*fmt == '%') + 1 * (*fmt == 'c')
				+ 2 * (*fmt == 's') + 3 * (*fmt == 'i' || *fmt == 'd')
				+ 4 * (*fmt == 'u') + 5 * (*fmt == 'x')
				+ 6 * (*fmt == 'X') + 7 * (*fmt == 'p');
			ret += option[id](args);
			fmt++;
		}
	}
	return (ret);
}

int	ft_printf(const char *fmt, ...)
{
	int		(*option[8])(va_list);
	va_list	args;
	int		ret;

	/* Init */
	ret = 0;
	option[0] = ft_pct;
	option[1] = ft_chr;
	option[2] = ft_str;
	option[3] = ft_nbr;
	option[4] = ft_uni;
	option[5] = ft_hx1;
	option[6] = ft_hx2;
	option[7] = ft_ptr;
	va_start(args, fmt);
	ret = parser(option, fmt, args);
	va_end(args);
	return (ret);
}
