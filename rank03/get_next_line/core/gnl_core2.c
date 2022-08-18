/* 8min + 6min debug */

char	*ft_newline(const char *temp)
{
	unsigned int	i;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	i += (temp[i] == '\n');
	return (ft_substr (temp, 0, i));
}

char	*ft_newtemp(char *temp)
{
	char			*new;
	unsigned int	i;

	i = 0;
	while (temp[i] && temp[i] != '\n')
		i++;
	i += (temp[i] == '\n');
	if (temp[i] == '\0')
		return (free (temp), NULL);
	new = ft_substr (temp, i, ft_strlen (temp) - i);
	return (free (temp), new);
}

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;
	char		*buf;
	long		rd;

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	buf = malloc (sizeof (*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	rd = 1;
	while (rd && !ft_has_nl (temp))
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (free (buf), NULL);
		buf[rd] = '\0';
		temp = ft_strjoin_free_s1 (temp, buf);
	}
	free (buf);
	if (!temp)
		return (NULL);
	line = ft_newline (temp);
	temp = ft_newtemp (temp);
	return (line); // XXX 6min… return line not temp!!
}
