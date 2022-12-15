#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

/*
 ** Tools:
 **
 ** #include <sys/stat.h>
 ** struct stat information;
 ** fstat (*prevpipe, &information);
 **
 ** valgrind -q --trace-children=yes --track-fds=yes
 */

void	ft_perror(char *s1, char *s2)
{
	while (s1 && *s1)
		write (STDERR_FILENO, s1++, 1);
	while (s2 && *s2)
		write (STDERR_FILENO, s2++, 1);
	write (STDERR_FILENO, "\n", 1);
}

void	ft_fatal(void)
{
	write (STDERR_FILENO, "error: fatal\n", 13);
	exit (1);
}

void	ft_program(char **cmd, int len, char **env, int *prevpipe)
{
	pid_t	cpid;

	cpid = fork ();
	if (cpid == -1)
		ft_fatal ();
	else if (cpid == 0)
	{
		dup2 (*prevpipe, STDIN_FILENO);
		close (*prevpipe);
		cmd[len] = NULL;
		if (execve (cmd[0], cmd, env) == -1)
			ft_perror ("error: cannot execute ", cmd[0]);
	}
	else
	{
		while (wait (NULL) != -1)
			;
	}
}

void	ft_pipe(char **cmd, int len, char **env, int *prevpipe)
{
	int		pipefd[2];
	pid_t	cpid;

	pipe (pipefd);
	cpid = fork ();
	if (cpid == -1)
		ft_fatal ();
	else if (cpid == 0)
	{
		close (pipefd[0]);
		dup2 (*prevpipe, STDIN_FILENO);
		close (*prevpipe);
		dup2 (pipefd[1], STDOUT_FILENO);
		close (pipefd[1]);
		cmd[len] = NULL;
		if (execve (cmd[0], cmd, env) == -1)
			ft_perror ("error: cannot execute ", cmd[0]);
	}
	else
	{
		close (pipefd[1]);
		close (*prevpipe);
		*prevpipe = pipefd[0];
	}
}

void	ft_cd(char **cmd, int len)
{
	if (len != 2)
		ft_perror ("error: cd: bad arguments", NULL);
	else if (chdir (cmd[1]) == -1)
		ft_perror ("error: cd: cannot change directory to ", cmd[1]);
}

int	ft_len(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && *cmd[len] != '|' && *cmd[len] != ';')
		len++;
	return (len);
}

int	main(int ac, char **cmd, char **env)
{
	int	len;
	int	prevpipe;

	(void)ac;
	len = 0;
	prevpipe = dup (STDIN_FILENO);
	while (cmd[len] && cmd[len + 1])
	{
		cmd += 1 + len;
		len = ft_len (cmd);
		if (*cmd[0] == ';')
			continue ;
		else if (!strcmp(cmd[0], "cd"))
			ft_cd (cmd, len);
		else if (cmd[len] && *cmd[len] == '|')
			ft_pipe (cmd, len, env, &prevpipe);
		else if (cmd[len] == NULL || *cmd[len] == ';')
			ft_program (cmd, len, env, &prevpipe);
	}
	close (prevpipe);
	return (0);
}
