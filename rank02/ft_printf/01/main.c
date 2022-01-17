#include "ft_printf.h"
// p 09 sucks
int	main(void)
{
	int ret;
	char *nul = NULL;
	int *ptr;
	ret = 0;
	ptr = &ret;

	/* int *ptr; */
	/* int	nb = 2; */

	/* ptr = &nb; */
	/* ft_printf("c:%c s:%s p:%p i:%i u:%u x:%x X:%X %%\n", */
	/* 		'c', "ss", ptr, -42, 42, 42, 42); */
	ret = ft_printf("0:%s s:%s c:%c s:%s i:%i u:%u x:%x X:%X p:%p %%\n", nul, "mine", 'c', "salut", -42, -42, 42, -42, ptr);
	printf("%i\n", ret);

	ret = printf("0:%s s:%s c:%c s:%s i:%i u:%u x:%x X:%X p:%p %%\n", nul, "orig", 'c', "salut", -42, -42, 42, -42, ptr);
	printf("%i\n", ret);
}
