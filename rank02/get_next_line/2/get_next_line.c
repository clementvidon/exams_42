#include "get_next_line.h"

static char	*ft_update_temp(char *temp)
{
	char	*new;
	size_t	i;

	i = 0;
	while (temp[i] && temp[i] != '\n') // check temp[i]
		i++;
	if (temp[i] == '\0')
	{
		free(temp);
		return (NULL);
	}
	if (temp[i] == '\n')
		i++;
	new = ft_strdup(&temp[i]);
	free(temp);
	return (new);
}

static char	*ft_getline(char *temp)
{
	size_t		i;

	if (*temp == '\0') // print (null) if EOF reached
		return (NULL); // only if substr return strdup inst NULL
	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	return (ft_substr(temp, 0, i));
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;
	char		*buf;
	long		r;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	r = 1;
	while (r && !ft_has_nl(temp))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r < 0)
			return (NULL);
		buf[r] = '\0'; // yes r is that useful
		temp = ft_strjoin(temp, buf);
	}
	free(buf); // not inside the while please
	if (!temp)
		return (NULL);
	line = ft_getline(temp);
	temp = ft_update_temp(temp);
	return (line);
}
