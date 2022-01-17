#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* Mandatory */
# include <unistd.h>
# include <stdlib.h>

/* Temporary */
# include <fcntl.h>
# include <stdio.h>

/* Macro */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

/* Core */
char	*get_next_line(int fd);

/* Utils */
size_t	ft_has_nl(char *str);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *str, size_t start, size_t len);

#endif
