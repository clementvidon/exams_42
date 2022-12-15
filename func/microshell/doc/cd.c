#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

void	ft_pipe(char **cmd, int cmdlen, char **env, int *prevpipe)
{
	int		pipefd[2];
	pid_t	cpid;

	pipe (pipefd);
	cpid = fork ();
	if (cpid == 0)
	{
		// close the read end of the pipe
		// connect Stdin to prev pipe
		// connect Stdout to write end of the pipe
		close (pipefd[0]);
		dup2 (*prevpipe, STDIN_FILENO);
		close (*prevpipe);
		dup2 (pipefd[1], STDOUT_FILENO);
		close (pipefd[1]);
		cmd[cmdlen] = NULL;
		execve (cmd[0], cmd, env);
	}
	else
	{
		// close the write end of the pipe
		// update prevpipe to pass the read end to the next child
		close (pipefd[1]);
		close (*prevpipe);
		*prevpipe = pipefd[0];
	}
}

void	ft_program(char **cmd, int cmdlen, char **env, int prevpipe)
{
	pid_t	cpid;

	cpid = fork ();
	if (cpid == 0)
	{
		// connect Stdin to prev pipe read end
		dup2 (prevpipe, STDIN_FILENO);
		close (prevpipe);
		cmd[cmdlen] = NULL;
		execve (cmd[0], cmd, env);
	}
	else
	{
		// close useless prevpipe
		close (prevpipe);
		while (wait (NULL) != -1)
			;
	}
}

int	ft_cmdlen(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && *cmd[len] != '|' && *cmd[len] != ';')
		len++;
	return (len);
}

void	ft_cd(char **cmd, int cmdlen)
{
	if (cmdlen != 2)
		dprintf (1, "error: cd: bad arguments\n");
	else if (chdir (cmd[1]) == -1)
		dprintf (1, "error: cd: cannot change directory to path_to_change\n");
}

int	main(int ac, char **av, char **env)
{
	int	cmdlen;
	int	prevpipe;

	(void)ac;
	cmdlen = 0;
	prevpipe = dup (0);
	while (av[cmdlen] && av[cmdlen + 1])
	{
		av += cmdlen + 1;
		cmdlen = ft_cmdlen (av);
		if (!strcmp (av[0], "cd"))
		{
			dprintf (1, "ft_cd\n");
			ft_cd (av, cmdlen);
		}
		else if (av[cmdlen] && *av[cmdlen] == '|')
		{
			dprintf (1, "ft_pipe\n");
			ft_pipe (av, cmdlen, env, &prevpipe);
		}
		else if (av[cmdlen] == NULL || *av[cmdlen] == ';')
		{
			dprintf (1, "ft_program\n");
			ft_program (av, cmdlen, env, prevpipe);
		}
	}
	return (0);
}

