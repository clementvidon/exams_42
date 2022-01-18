#include "ft_printf.h"

int	main(void)
{
	int		*ptr;
	int		ft_ret;
	int		ret;

	ptr = &ret;

	ft_ret = ft_printf("hey %c %% %s %i%d %u salut%x %X %p\n",
			'C', "ss", -42, -42, -42, -42, -42, ptr);
	printf(">>>%i<<<\n",ft_ret);

	ret = printf("hey %c %% %s %i%d %u salut%x %X %p\n",
			'C', "ss", -42, -42, -42, -42, -42, ptr);
	printf(">>>%i<<<\n",ret);

	return (0);
}
