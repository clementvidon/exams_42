#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*out;

	fd = open("file", O_RDONLY);
	if (fd < 0)
		return (1);

	out = get_next_line(fd);
	printf("%s", out);
	free (out);
	out = get_next_line(fd);
	printf("%s", out);
	free (out);
	out = get_next_line(fd);
	printf("%s", out);
	free (out);
	out = get_next_line(fd);
	printf("%s", out);
	free (out);
	out = get_next_line(fd);
	printf("%s", out);
	free (out);

	out = get_next_line(fd);
	printf("%s", out);
	free (out);
	out = get_next_line(fd);
	printf("%s", out);
	free (out);
	/* out = get_next_line(fd); */
	/* printf("%s\n", out); */
	return (0);
}
