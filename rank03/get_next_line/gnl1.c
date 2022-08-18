/* ** PREPROC >>> */
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

/* <<<
 ** GNL UTILS >>>
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

/* <<<
 ** GNL >>>
 */

/*
 ** @brief      Extract the first line it finds in temp.
 **
 ** @param[in]  temp can be the next line [ and more ] or NULL.
 ** @return     The next line to taken from temp content.
 */

/*
 ** @brief      Update temp to pass to the next line it contains or NULL if
 **             there is nothing left to read.
 **
 ** @param[in]  temp can be the next line [ and more ] or NULL.
 ** @return     A new temp starting from the next line to read or NULL.
 */

/*
 ** @brief      Get the next line of text available on a file descriptor.
 **
 ** Calling get_next_line in a loop will allow us to read the text available on
 ** the file descriptor one line at a time until the end of it.
 **
 ** A line is defined as a NUL or LF terminated string.
 **
 ** @var        temp can be:
 **              - the next line, if BUFFER_SIZE is smaller than a line.
 **              - the next line and more, if BUFFER_SIZE is bigger than a line.
 **              - NULL if there are no text left to read on the filedes.
 ** @var        line is the next line to be returned.
 ** @var        buf is for read(2) buffer.
 ** @var        rd is for read(2) return value.
 **
 ** @param[in]  fd the file descriptor.
 ** @return     The line that has just been read or NULL.
 */

/* <<<
 ** MAIN >>>
 */

int	main(void)
{
	int		fd;
	char	*ret;

	fd = open("file", O_RDONLY);

		printf("---start---\n");
	while (1)
	{
		ret = get_next_line(fd);
		if (!ret)
			break ;
		printf("%s", ret);
		free(ret);
	}
		printf("---finish--\n");
}
/* <<< */
