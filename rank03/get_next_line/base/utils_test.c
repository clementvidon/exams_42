#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

// ft_has_nl
// ft_strlen
// ft_strdup
// ft_strjoin

size_t	ft_has_nl(const char *str)
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
		ptr++;
	return ((size_t)(ptr - str));
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	char	*p2;

	if (!s1)
		return (NULL);
	s2 = malloc (sizeof (char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	p2 = s2;
	while (*s1)
		*p2++ = *s1++;
	return (*p2 = 0, s2);
}

char	*ft_strjoin(char *s1, const char *s2)
{
	char	*s3;
	char	*tmp1;
	char	*tmp3;

	if (!s1 && s2)
		return (ft_strdup (s2));
	if (s1 && !s2)
		return (ft_strdup (s1));
	if (!s1 && !s2)
		return (ft_strdup (""));
	s3 = malloc (sizeof (char) * (ft_strlen (s1) + ft_strlen (s2) + 1));
	if (!s3)
		return (free (s1), NULL);
	tmp1 = s1;
	tmp3 = s3;
	while (*tmp1)
		*tmp3++ = *tmp1++;
	while (*s2)
		*tmp3++ = *s2++;
	return (*tmp3 = 0, free (s1), s3);
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

int	main(void)
{
	char	*str = "salut\nsalut";
	char	*dup;
	char	*sub;
	char	*join;

	(void)str;
	(void)dup;
	(void)sub;
	(void)join;

	dprintf(2, "has_nl> %zu\n", ft_has_nl(str));

	dprintf(2, "strlen> %zu\n", ft_strlen(str));
	dup = ft_strdup(str);
	dprintf(2, "strdup> %s\n", dup);

	sub = ft_substr(dup, 6, 10);
	dprintf(2, "substr> %s\n", sub);

	join = ft_strjoin(dup, " mec");
	dprintf(2, "stjoin> %s\n", join);

	free (sub);
	free (join);
}
