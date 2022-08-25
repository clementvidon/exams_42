#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

///////////////////////////

ssize_t	ft_str(char const *str)
{
	size_t	len;

	if (!str)
		return (write (1, "(null)", 6));
	len = 0;
	while (str[len])
		len++;
	return (write (1, str, len));
}

void	ft_nbr(int n, ssize_t *r)
{
	long		ln;

	ln = n;
	if (ln < 0)
	{
		ln = -ln;
		*r += write (1, "-", 1);
	}
	if (ln >= 10)
		ft_nbr ((int)(ln / 10), r);
	*r += write (1, &"0123456789"[ln % 10], 1);
}

void	ft_hex(unsigned int n, ssize_t *r)
{
	if (n >= 16)
		ft_hex ((unsigned int)(n / 16), r);
	*r += write (1, &"0123456789abcdef"[n % 16], 1);
}

///////////////////////////

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	ssize_t	r;

	r = 0;
	va_start (args, fmt);
	while (*fmt)
	{
		if (*fmt != '%')
			r += write (1, fmt, 1);
		else if (*(fmt + 1))
		{
			fmt++;
			if (*fmt == 's')
				r += ft_str (va_arg (args, char *));
			if (*fmt == 'i')
				ft_nbr (va_arg (args, int), &r);
			else if (*fmt == 'x')
				ft_hex (va_arg (args, unsigned int), &r);
		}
		fmt++;
	}
	va_end (args);
	return ((int)r);
}
