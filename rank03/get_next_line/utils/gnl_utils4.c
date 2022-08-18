#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

/*
 ** ft_has_nl:		1min20
 ** ft_strlen:		1min
 ** ft_strdup:		2min30
 ** ft_strjoin:		3min10
 ** ft_substr:		3min30
 */

int	ft_has_nl(char const *str)
{
	if (str)
		while (*str && *str != '\n')
			str++;
	return (str && *str == '\n');
}

size_t	ft_strlen(char const *str)
{
	char const	*ptr;

	ptr = str;
	while (*ptr)
		++ptr;
	return ((size_t)(ptr - str));
}

char	*ft_strdup(char const *str)
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

char	*ft_strjoin_free_s1(char *s1, char const *s2)
{
	char	*s3;
	char	*p3;
	char	*p1;

	if (s1 && !s2)
		return (ft_strdup (s1));
	if (!s1 && s2)
		return (ft_strdup (s2));
	if (!s1 && !s2)
		return (ft_strdup (""));
	s3 = malloc (sizeof (*s3) * (ft_strlen (s1) + ft_strlen (s2) + 1));
	if (!s3)
		return (free (s1), NULL);
	p1 = s1;
	p3 = s3;
	while (*p1)
		*p3++ = *p1++;
	while (*s2)
		*p3++ = *s2++;
	return (*p3 = 0, free (s1), s3); // XXX don't forget *p3 = 0
}

char	*ft_substr(const char *str, unsigned int start, size_t size)
{
	char	*sub;
	size_t	len;

	if (!str)
		return (NULL);
	len = ft_strlen (str);
	if (start >= len)
		return (NULL);
	if (len - start < size)
		size = len - start;
	sub = malloc (sizeof (*sub) * (size + 1));
	if (!sub)
		return (NULL);
	sub[size] = 0;
	while (size--)
		sub[size] = str[start + size];
	return (sub);
}
