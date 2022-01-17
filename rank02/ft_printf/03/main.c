#include "ft_printf.h"

int	main(void)
{
	int		ret___1;
	int		ret2;
	char	c = 'X';
	char	*s = "salut";
	char	*n = NULL;

	ret___1 = printf("salut %% %c %s %s %i %u %x %p\n", c, s, n, -42, -42, -42, &s);
	ret2 = ft_printf("salut %% %c %s %s %i %u %x %p\n", c, s, n, -42, -42, -42, &s);
	printf("%i == %i\n", ret___1, ret2);
}
