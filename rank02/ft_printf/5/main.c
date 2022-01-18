#include "ft_printf.h"

int	main(void)
{
	int		ret0;
	int		ret1;
	char	*s = "s";
	char	*null = NULL;

	ret0 = 0;
	ret1 = 0;
	ret0 = ft_printf("salut %% %c %s %s %i %u %x %p\n", 'c', s, null, 42, -42, -42, s);
	ret1 =    printf("salut %% %c %s %s %i %u %x %p\n", 'c', s, null, 42, -42, -42, s);
	printf("%i == %i", ret0, ret1);
	return(0);
}
