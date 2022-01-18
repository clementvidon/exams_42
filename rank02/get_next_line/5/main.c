#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*ret;

	fd = open("file", O_RDONLY);

	ret = get_next_line(fd);
	printf("%s\n", ret);
	free(ret);

	ret = get_next_line(fd);
	printf("%s\n", ret);
	free(ret);

	ret = get_next_line(fd);
	printf("%s\n", ret);
	free(ret);

	ret = get_next_line(fd);
	printf("%s\n", ret);
	free(ret);

	ret = get_next_line(fd);
	printf("%s\n", ret);
}
