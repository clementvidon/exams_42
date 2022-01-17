#include "get_next_line.h"

static char	*ft_newline(char *temp)
{
	size_t	i;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\n')
		i++;
	return (ft_substr(temp, 0, i));
}

static char	*ft_newtemp(char *temp)
{
	char	*new;
	size_t	i;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	if (temp[i] == '\0')
		return (free (temp), NULL);
	if (temp[i] == '\n')
		i++;
	new = ft_substr(temp, i, ft_strlen(temp) - i);
	return (free(temp), new);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;
	char		*buf;
	long		r;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buf = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	r = 1;
	while (r && !ft_has_nl(temp))
	{
		r = read (fd, buf, BUFFER_SIZE);
		if (r < 0)
			return (free(buf), NULL); // FREE BUF !!!!!!!
		buf[r] = '\0';
		temp = ft_strjoin(temp, buf);
	}
	free (buf);
	if (!temp)
		return (NULL);
	line = ft_newline(temp);
	temp = ft_newtemp(temp);
	return (line);
}
