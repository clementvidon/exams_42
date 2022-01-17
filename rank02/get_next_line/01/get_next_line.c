#include "get_next_line.h"

static int	ft_locate_nl(char *str)
{
	while (str && *str) // ne pas oublier de check str
		if (*str++ == '\n')
			return (1);
	return (0);
}

static char	*ft_update_temp(char *temp)
{
	char			*new;
	unsigned int	i;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\0')
		return (ft_free(temp));
	if (temp[i] == '\n')
		i++;
	new = ft_substr(temp, i, ft_strlen(temp) - i);
	ft_free(temp);
	return (new);
}

static char	*ft_get_line(char *temp)
{
	unsigned int	i;

	if (*temp == '\0')
		return (NULL);
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	return (ft_substr(temp, 0, i));
}

char	*get_next_line(int fd)
{
	static char		*temp = NULL;
	char			*line;
	char			*buf;
	long			r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	r = 1;
	while(r && !ft_locate_nl(temp))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
			return (ft_free(buf));
		buf[r] = '\0';
		temp = ft_strjoin(temp, buf);
	}
	ft_free(buf);
	if (!temp)
		return (NULL);
	line = ft_get_line(temp);
	temp = ft_update_temp(temp);
	return (line);
}
