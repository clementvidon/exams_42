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
	unsigned int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(char *s1)
{
	char	*s2;
	char	*ptr;

	s2 = malloc (sizeof(char) * ((unsigned long)ft_strlen(s1) + 1));
	if (!s2)
		return (NULL);
	ptr = s2;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	int		i;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	s3 = malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	i = -1;
	while (s2[++i])
		s3[ft_strlen(s1) + (size_t)i] = s2[i];
	s3[ft_strlen(s1) + (size_t)i] = s2[i];
	free (s1);
	return (s3);
}

char	*ft_substr(char *s1, size_t start, size_t len)
{
	char	*s2;
	size_t	i;

	if (!s1)
		return (NULL);
	if (start >= ft_strlen(s1))
		return (ft_strdup("")); // strdup != NULL
	s2 = malloc (sizeof(char) * (len + 1)); // len != strlen(s1)
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] && i < len) // s1[i] !!
	{
		s2[i] = s1[start + i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
