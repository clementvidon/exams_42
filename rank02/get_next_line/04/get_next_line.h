#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

/* Includes */
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
/* Extra */
# include <stdio.h>

/* Proto */
char	*get_next_line(int fd);
int		ft_has_nl(char *str);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *str, size_t start, size_t len);

#endif
