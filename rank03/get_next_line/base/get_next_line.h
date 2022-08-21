#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000000
# endif

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *str);
char	*ft_strjoin_free_s1 (char *s1, const char *s2);
char	*ft_substr(const char *str, unsigned int start, size_t size);

char	*get_next_line(int fd);

#endif
