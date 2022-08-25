#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_has_nl (const char *str)
{
	if (str)
		while (*str && *str != '\n')
			++str;
	return (str && *str == '\n');
}

size_t	ft_strlen (const char *str)
{
	const char	*ptr;

	ptr = str;
	while (*ptr)
		++ptr;
	return ((size_t)(ptr - str));
}

char	*ft_strdup (const char *str)
{
	char	*dup;
	char	*ptr;

	if (!str)
		return (NULL);
	dup = malloc (sizeof (*dup) * (ft_strlen (str) + 1));
	if (!dup)
		return (NULL);
	ptr = dup;
	while (*str)
		*ptr++ = *str++;
	return (*ptr = 0, dup);
}

char	*ft_strjoin_free_s1 (char *s1, const char *s2)
{
	char	*s3;
	char	*p3;
	char	*p1;

	if (!s1 && !s2)
		return (ft_strdup (""));
	if (!s1 && s2)
		return (ft_strdup (s2)); // 2 XXX confuse s1/s2
	if (s1 && !s2)
		return (ft_strdup (s1)); // 2 XXX confuse s1/s2
	s3 = malloc (sizeof (*s3) + (ft_strlen (s1) + ft_strlen (s2) + 1));
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

char	*ft_substr (const char *str, unsigned int start, size_t size)
{
	char	*sub;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen (str);
	if (start >= len)
		return (NULL); // 1 XXX return (NULL)
	if (len - start < size)
		size = len - start;
	sub = malloc (sizeof (*sub) * (size + 1)); // 1 XXX + 1
	if (!sub)
		return (NULL);
	sub[size] = 0;
	while (size--) // 1 XXX not str[size--]
		sub[size] = str[start + size];
	return (sub);
}

// TODO si str[i] = 0 alors on return NULL, ainsi je peux retirer NULL de substr et remettre stdup("") ?

char	*ft_line (const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	i += (str[i] == '\n');
	return (ft_substr (str, 0, i));
}

char	*ft_temp (char *str)
{
	char	*temp;
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (free (str), NULL);
	i += (str[i] == '\n');
	temp = ft_substr (str, (unsigned int)i, ft_strlen (str) - i); // 2 XXX "strlen (str) - i" NOT "i"
	return (free (str), temp);
}

char	*get_next_line (int fd)
{
	static char	*temp; // 1 XXX static
	char		*line;
	char		*buf;
	ssize_t		r; // TODO ssize_t instead of long

	if (fd == -1 || BUFFER_SIZE < 1)
		return (NULL);
	buf = malloc (sizeof (*buf) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	r = 1;
	while (r && !ft_has_nl (temp))
	{
		r = read (fd, buf, BUFFER_SIZE);
		if (r == -1)
			return (free (buf), NULL);
		buf[r] = 0;
		temp = ft_strjoin_free_s1 (temp, buf);
	}
	free (buf);
	if (!temp)
		return (NULL);
	line = ft_line (temp);
	temp = ft_temp (temp);
	return (line);
}
