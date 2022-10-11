#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include <stdlib.h>
#include <sys/types.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i ++;
	return (i);
}

void	ft_putstr_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

void	ft_exec(char **av, int i, int fd, char **env)
{
	av[i] = NULL;
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (execve(av[0], av, env) == -1)
	{
		ft_putstr_fd(2, "error: cannot execute ");
		ft_putstr_fd(2, av[0]);
		write(2, "\n", 1);
		exit (EXIT_FAILURE);
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	pid;
	int	fd_cpy;
	int fd[2];

	i = 0;
	pid = 0;
	fd_cpy = dup(STDIN_FILENO);
	(void) ac;
	while (av[i] && av[i + 1])
	{
		av = &av[i + 1];
		i = 0;
		while (av[i] && strcmp(av[i], ";") && strcmp(av[i], "|"))
			i ++;
		if (i != 0 && !strcmp(av[0], "cd"))
		{
			if (i != 2)
				ft_putstr_fd(2, "error: cd: bad arguments\n");
			else if (chdir(av[1]) == -1)
			{
				ft_putstr_fd(2, "error: cd: cannot change directory to ");
				ft_putstr_fd(2, av[1]);
				write(2, "\n", 1);
				/* exit(EXIT_FAILURE); */
				/* la ligne commentée doit restée commentée (effacée) et pendant */
				/* l'exam il faudra que tu protèges tous les appels systèmes */
				/* (c'est demandé dans le sujet de l'exam) */
			}
		}
		else if (i != 0 && (av[i] == NULL || !strcmp(av[i], ";")))
		{
			pid = fork();
			if (pid == 0)
				ft_exec(av, i, fd_cpy, env);
			else
			{
				close(fd_cpy);
				while (waitpid(0, 0, 0) != -1)
					;
				fd_cpy = dup(STDIN_FILENO);
			}
		}
		else if (i != 0 && !strcmp(av[i], "|"))
		{
			pipe(fd);
			pid = fork();
			if (pid == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				ft_exec(av, i, fd_cpy, env);
			}
			else
			{
				close(fd[1]);
				close(fd_cpy);
				fd_cpy = fd[0];
			}
		}
	}
	close(fd_cpy);
	close(fd[0]);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

