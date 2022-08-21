#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*ret;

	fd = open("file", O_RDONLY);

	while (1)
	{
		ret = get_next_line(fd);
		if (!ret)
			break ;
		write (1, ret, ft_strlen(ret));
		free(ret);
	}
}
