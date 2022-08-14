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
size_t	ft_has_nl(char const *str);
size_t	ft_strlen(char const *str);
char	*ft_strdup(char const *str);
char	*ft_strjoin_free_s1(char *s1, char const *s2);
char	*ft_substr(char const *str, unsigned int start, size_t size);

#endif
