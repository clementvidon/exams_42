#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* Mandatory */
# include <unistd.h>
# include <stdlib.h>

/* Temporary */
# include <fcntl.h>
# include <stdio.h>

/* Define */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

/* Core */
char	*get_next_line(int fd);

/* Utils */
size_t	ft_has_nl(const char *str);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strjoin(char *s1, const char *s2);
char	*ft_substr(const char *str, unsigned int start, size_t size);

#endif
