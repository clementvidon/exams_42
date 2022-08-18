#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

/*
 ** ft_has_nl:		1min
 ** ft_strlen:		1min
 ** ft_strdup:		3min
 ** ft_strjoin:		4min
 ** ft_substr:		3min
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
		ptr++;
	return ((size_t)(ptr - str));
}

char	*ft_strdup(char const *s1)
{
	char	*s2;
	char	*p2;

	if (!s1)
		return (NULL);
	s2 = malloc (sizeof (*s2) * (ft_strlen (s1) + 1));
	if (!s2)
		return (NULL);
	p2 = s2;
	while (*s1)
		*p2++ = *s1++;
	return (*p2 = 0, s2);
}

char	*ft_strjoin_free_s1(char *s1, char const *s2)
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
	s3 = malloc (sizeof (*s3) * (ft_strlen (s1) + ft_strlen (s2) + 1));
	if (!s3)
		return (free (s1), NULL);
	p3 = s3;
	p1 = s1;
	while (*p1)
		*p3++ = *p1++;
	while (*s2)
		*p3++ = *s2++;
	return (free (s1), *p3 = 0, s3);
}

char	*ft_substr(char const *str, unsigned int start, size_t size)
{
	size_t	len;
	char	*sub;

	if (!str)
		return (NULL);
	len = ft_strlen (str);
	if (len <= start)
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

int	main(void)
{
	char	*dup;
	char	*sub;
	char	*join;

	(void)dup;
	(void)sub;
	(void)join;

	dprintf(2, "has_nl> %i == 1\n", ft_has_nl("salut \n salut"));
	dprintf(2, "has_nl> %i == 1\n", ft_has_nl("salutsalut\n"));
	dprintf(2, "has_nl> %i == 1\n", ft_has_nl("\nsalutsalut\n"));
	dprintf(2, "has_nl> %i == 1\n", ft_has_nl("s\nalutsalut"));
	dprintf(2, "has_nl> %i == 0\n", ft_has_nl("s alutsalu t"));
	dprintf(2, "has_nl> %i == 1\n", ft_has_nl("s\nalutsalu\nt"));

	dprintf(2, "strlen> %zu == 0\n", ft_strlen(""));
	dprintf(2, "strlen> %zu == 1\n", ft_strlen("0"));
	dprintf(2, "strlen> %zu == 5\n", ft_strlen("01234"));

	dup = ft_strdup("cloned one");
	dprintf(2, "strdup> '%s' == 'cloned one'\n", dup);
	free (dup);
	dup = ft_strdup("");
	dprintf(2, "strdup> '%s' == ''\n", dup);
	free (dup);
	dup = ft_strdup("salut");
	dprintf(2, "strdup> '%s' == 'salut'\n", dup);
	free (dup);

	join = ft_strjoin_free_s1(ft_strdup("salut"), " mec");
	dprintf(2, "stjoin> %s == salut mec\n", join);
	free (join);
	join = ft_strjoin_free_s1(ft_strdup(""), "mec");
	dprintf(2, "stjoin> %s == mec\n", join);
	free (join);
	join = ft_strjoin_free_s1(ft_strdup("mec"), "");
	dprintf(2, "stjoin> %s == mec\n", join);
	free (join);
	join = ft_strjoin_free_s1(ft_strdup(""), "");
	dprintf(2, "stjoin> %s == \n", join);
	free (join);
	join = ft_strjoin_free_s1(ft_strdup("sara"), "bay");
	dprintf(2, "stjoin> '%s' == 'sarabay' \n", join);
	free (join);

	sub = ft_substr("123456789", 6, 15);
	dprintf(2, "substr> %s == 789\n", sub);
	free (sub);
	sub = ft_substr("123456789", 0, 1);
	dprintf(2, "substr> %s == 1\n", sub);
	free (sub);
	sub = ft_substr("123456789", 8, 5);
	dprintf(2, "substr> %s == 1\n", sub);
	free (sub);

}
