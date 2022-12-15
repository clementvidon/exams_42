#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void	ft_fatal ()
{
	write (2, "error: fatal\n", 13);
	exit (1);
}

void	ft_perror (char *s1, char *s2)
{
	while (s1 && *s1)
		write (2, s1++, 1);
	while (s2 && *s2)
		write (2, s2++, 1);
	write (2, "\n", 1);
}

void	ft_program (char **cmd, int len, char **env, int *prevpipe)
{
	pid_t	cpid;

	cpid = fork ();
	if (cpid == -1)
		ft_fatal ();
	else if (cpid == 0)
	{
		if (dup2 (*prevpipe, STDIN_FILENO) == -1)
			ft_fatal ();
		if (close (*prevpipe) == -1)
			ft_fatal ();
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

	if (pipe (pipefd) == -1)
		ft_fatal ();
	cpid = fork ();
	if (cpid == -1)
		ft_fatal ();
	else if (cpid == 0)
	{
		if (close (pipefd[0]) == -1)
			ft_fatal ();
		if (dup2 (*prevpipe, STDIN_FILENO) == -1)
			ft_fatal ();
		if (close (*prevpipe) == -1)
			ft_fatal ();
		if (dup2 (pipefd[1], STDOUT_FILENO) == -1)
			ft_fatal ();
		if (close (pipefd[1]) == -1)
			ft_fatal ();
		cmd[len] = NULL;
		if (execve (cmd[0], cmd, env) == -1)
			ft_perror ("error: cannot execute ", cmd[0]);
	}
	else
	{
		if (close (pipefd[1]) == -1)
			ft_fatal ();
		if (close (*prevpipe) == -1)
			ft_fatal ();
		*prevpipe = pipefd[0];
	}
}

void	ft_cd (char **cmd, int len)
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
	int	prevpipe;
	int	len;

	(void) ac;
	prevpipe = dup (STDIN_FILENO);
	if (prevpipe == -1)
		ft_fatal ();
	len = 0;
	while (cmd[len] && cmd[len + 1])
	{
		cmd += 1 + len;
		len = ft_len (cmd);
		if (*cmd[0] == ';')
			continue ;
		else if (!strcmp (cmd[0], "cd"))
			ft_cd (cmd, len);
		else if (cmd[len] && *cmd[len] == '|')
			ft_pipe (cmd, len, env, &prevpipe);
		else if (cmd[len] == NULL || *cmd[len] == ';')
			ft_program (cmd, len, env, &prevpipe);
	}
	if (close (prevpipe) == -1)
		ft_fatal ();
	return (0);
}
