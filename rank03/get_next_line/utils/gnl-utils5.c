/*
 ** ft_has_nl:		1min
 ** ft_strlen:		1min30
 ** ft_strdup:		3min
 ** ft_strjoin:		5min
 ** ft_substr:		7min
 ** TOTAL: 			16min
 */

int	ft_has_nl(const char *str)
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
	char	*ptr;
	char	*dup;

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

char	*ft_strjoin_free_s1(char *s1, const char *s2)
{
	char	*s3;
	char	*p3;
	char	*p1;

	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (!s1 && !s2)
		return (ft_strdup(""));
	s3 = malloc (sizeof (*s3) * (ft_strlen (s1) + ft_strlen (s2) + 1));
	if (!s3)
		return (free (s1), NULL);
	p3 = s3;
	p1 = s1;
	while (*p1)
		*p3++ = *p1++;
	while (*s2)
		*p3++ = *s2++;
	return (*p3 = 0, free (s1), s3); // XXX *p3 not *s3
}

char	*ft_substr (const char *str, unsigned int start, size_t size)
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
