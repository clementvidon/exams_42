#include <stdio.h>
#include <limits.h>

int	ft_printf(const char *fmt, ...);

int	main(void)
{
	int		ret;
	char	*null;

	null = NULL;

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
