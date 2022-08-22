#include <stdarg.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>

/*
 ** TODO
 **
 ** Replace else-if forest with array/define/funptr fully scalable system.
 */

///////////////////////////

ssize_t	ft_str (const char *str)
{
	size_t	len;

	if (!str)
		return (write (1, "(null)", 6));
	len = 0;
	while (str[len])
		len++;
	return (write (1, str, len));
}

void	ft_nbr (int n, ssize_t *r)
{
	long	ln;

	ln = n;
	if (ln < 0)
	{
		ln = -ln;
		*r += write (1, "-", 1);
	}
	if (ln >= 10)
		ft_nbr ((int)(ln / 10), r);
	*r += write (1, &"0123456789"[ln % 10], 1); // 1 XXX (int)(ln / 10) not (int)ln / 10
}

void	ft_hex (unsigned int n, ssize_t *r)
{
	if (n >= 16)
		ft_hex (n / 16, r);
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
		else if (*(fmt + 1)) // 1 XXX "*(fmt + 1)" NOT "*fmt + 1" or SEGV
		{
			fmt++;
			if (*fmt == 's')
				r += ft_str (va_arg (args, char *));
			else if (*fmt == 'i')
				ft_nbr (va_arg (args, int), &r);
			else if (*fmt == 'x')
				ft_hex (va_arg (args, unsigned int), &r);
		}
		fmt++;
	}
	va_end (args);
	return ((int)r);
}

///////////////////////////

int	main(void)
{
	int		ret;
	char	*null = NULL;

	// SEGV
	ret =  ft_printf ("%");

	ret =  ft_printf ("");
	dprintf (1, " %i\n", ret);
	ret = dprintf (1, "");
	dprintf (1, " %i\n", ret);
	dprintf (1, "----------\n");

	// STR
	ret =  ft_printf ("'%s'", "");
	dprintf (1, " %i\n", ret);
	ret = dprintf (1, "'%s'", "");
	dprintf (1, " %i\n", ret);
	dprintf (1, "----------\n");

	// NBR
	ret =  ft_printf ("'%i'", 0);
	dprintf (1, " %i\n", ret);
	ret = dprintf (1, "'%i'", 0);
	dprintf (1, " %i\n", ret);
	dprintf (1, "----------\n");

	// HEX
	ret =  ft_printf ("'%x'", 0);
	dprintf (1, " %i\n", ret);
	ret = dprintf (1, "'%x'", 0);
	dprintf (1, " %i\n", ret);
	dprintf (1, "----------\n");

	// MIX
	ret =  ft_printf ("'salut %s %s	%i %i %i %x %x %x'", "", null, INT_MIN, INT_MAX, 0, INT_MAX, INT_MIN, 0);
	dprintf (1, " %i\n", ret);
	ret = dprintf (1, "'salut %s %s	%i %i %i %x %x %x'", "", null, INT_MIN, INT_MAX, 0, INT_MAX, INT_MIN, 0);
	dprintf (1, " %i\n", ret);
	dprintf (2, "----------\n");

	return (0);
}
