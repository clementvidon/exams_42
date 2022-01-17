#include "get_next_line.h"

int	ft_has_nl(char *str)
{
	while (str && *str)
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
	char	*cpy;
	int		i;

	if (!str)
		return (NULL);
	cpy = malloc (sizeof(char) * (ft_strlen(str) + 1));
	if (!cpy)
		return (NULL);
	i = -1;
	while (str[++i])
		cpy[i] = str[i];
	cpy[i] = '\0';
	return (cpy);
}

char	*ft_substr(char *str, size_t start, size_t len)
{
	char	*sub;
	size_t	i;

	if (start >= ft_strlen(str))
		return (NULL);
	sub = malloc (sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && str[start + i]) // start
	{
		sub[i] = str[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (s1 && !s2)
		return (ft_strdup(s1));
	if (!s1 && s2)
		return (ft_strdup(s2));
	s3 = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	i = -1;
	while (s2[++i])
		s3[i + (int)ft_strlen(s1)] = s2[i];
	s3[i + (int)ft_strlen(s1)] = '\0';
	free (s1);
	return (s3);
}
