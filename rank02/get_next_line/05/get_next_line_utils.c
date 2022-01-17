#include "get_next_line.h"

size_t	ft_has_nl(char *str)
{
	if (str)
		while (*str)
			if (*str++ == '\n')
				return (1);
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str)
{
	char	*dup;
	size_t	len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	dup = malloc (sizeof (char) * (len + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (str[++i])
		dup[i] = str[i];
	dup[i] = '\0';
	return (dup);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;

	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (ft_strdup(""));
	s3 = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	j = -1;
	while (s2[++j])
		s3[j + i] = s2[j];
	s3[j + i] = '\0';
	return (free(s1), s3);
}

char	*ft_substr(char *str, size_t start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	strlen;

	strlen = ft_strlen(str);
	if (start >= strlen)
		return (NULL);
	sub = malloc (sizeof (char) * (strlen + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (str[start + i] && i < len)
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
