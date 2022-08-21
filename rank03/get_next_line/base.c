/* 1044 */
/* 1139 */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static size_t	ft_has_nl(const char *str)
{
	if (str)
		while (*str && *str != '\n')
			str++;
	return (str && *str == '\n');
}

size_t	ft_strlen(const char *str)
{
	const char	*ptr;

	ptr = str;
	while (*ptr)
		++ptr;
	return ((size_t)(ptr - str));
}

char	*ft_strdup(const char *str)
{
	char	*dup;
	char	*ptr;

	if (!str)
		return (NULL);
	dup = malloc (sizeof (char) * (ft_strlen(str) + 1));
	if (!dup)
		return (NULL);
	ptr = dup;
	while (*str)
		*ptr++ = *str++;
	return (*ptr = 0, dup);
}

char	*ft_strjoin_free_s1(char *s1, const char *s2)
{
	char	*s3;
	char	*p3;
	char	*p1;

	if (!s1 && s2)
		return (ft_strdup (s2));
	if (s1 && !s2)
		return (ft_strdup (s1));
	if (!s1 && !s2)
		return (ft_strdup (""));
	s3 = malloc (sizeof (char) * (ft_strlen (s1) + ft_strlen (s2) + 1));
	if (!s3)
		return (free (s1), NULL);
	p3 = s3;
	p1 = s1;
	while (*p1)
		*p3++ = *p1++;
	while (*s2)
		*p3++ = *s2++;
	return (*p3 = 0, free (s1), s3);
}

char	*ft_substr(const char *str, unsigned int start, size_t size)
{
	size_t	len;
	char	*sub;

	if (!str)
		return (NULL);
	len = ft_strlen (str);
	if (start >= len)
		return (NULL);
	if (len - start < size)
		size = len - start;
	sub = malloc (sizeof (char) * (size + 1));
	if (!sub)
		return (NULL);
	sub[size] = 0;
	while (size--)
		sub[size] = str[start + size];
	return (sub);
}

static char	*ft_line(const char *temp)
{
	size_t	i;

	i = 0;
	while (temp[i] != '\0' && temp[i] != '\n')
		i++;
	i += (temp[i] == '\n');
	return (ft_substr (temp, 0, i));
}

static char	*ft_temp(char *temp)
{
	char			*new;
	unsigned int	i;

	i = 0;
	while (temp[i] != '\0' && temp[i] != '\n')
		i++;
	if (temp[i] == '\0')
		return (free (temp), NULL);
	i += (temp[i] == '\n');
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
	buf = malloc (sizeof (char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	rd = 1;
	while (rd && !ft_has_nl (temp))
	{
		rd = read (fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (free (buf), NULL);
		buf[rd] = '\0';
		temp = ft_strjoin_free_s1 (temp, buf);
	}
	free (buf);
	if (!temp)
		return (NULL);
	line = ft_line (temp); temp = ft_temp (temp);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*str;

	/* printf("%i 0\n", ft_has_nl ("salut")); */
	/* printf("%i 1\n", ft_has_nl ("salut\nsldkfjs")); */
	/* printf("%i 1\n", ft_has_nl ("t\n")); */
	/* printf("%i 1\n", ft_has_nl ("\n")); */
	/* printf("%i 1\n", ft_has_nl ("\nt")); */

	/* printf("%zu 5\n", ft_strlen ("salut")); */
	/* printf("%zu 6\n", ft_strlen ("salut\n")); */

	/* char *dup = ft_strdup ("dup"); */
	/* printf("%s dup\n", dup); */
	/* free (dup); */

	/* char *s1 = ft_strdup ("c"); */
	/* printf("%s cv\n", ft_strjoin_free_s1 (s1, "v")); */

	/* printf("%s cv\n", ft_substr ("salut mec", 5, 3)); */

	/* fd = open ("gnl1.c", O_RDONLY); */
	/* while (1) */
	/* { */
	/* 	str = get_next_line (fd); */
	/* 	if (!str) */
	/* 		return (1); */
	/* 	dprintf(2, "> %s\n", str); */
	/* 	free (str); */
	/* } */
	/* return (0); */

	fd = open ("gnl1.c", O_RDONLY);
	while (1)
	{
		str = get_next_line (fd);
		if (!str)
			break ;
		write (1, str, ft_strlen(str));
		free (str);
	}
	fd = open ("file", O_RDONLY);
	while (1)
	{
		str = get_next_line (fd);
		if (!str)
			break ;
		write (1, str, ft_strlen(str));
		free (str);
	}
	fd = open ("empty", O_RDONLY);
	while (1)
	{
		str = get_next_line (fd);
		if (!str)
			break ;
		write (1, str, ft_strlen(str));
		free (str);
	}
	return (0);
}
