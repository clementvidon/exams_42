#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

# define PIPEIN pipefd[0]
# define PIPEOUT pipefd[1]

int	ft_cmdlen(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && *cmd[len] != '|' && *cmd[len] != ';')
		len++;
	return (len);
}

void	ft_program(char **cmd, int cmdlen, char **env, int prevpipe)
{
	pid_t	cpid;

	cpid = fork ();
	if (cpid == 0)
	{
		dup2 (prevpipe, STDIN_FILENO);
		close (prevpipe);

		cmd[cmdlen] = NULL;
		execve (cmd[0], cmd, env);
	}
	else
	{
		close (prevpipe);
		while (wait (NULL) != -1)
			;
	}
}

/*
 ** @brief
 **
 ** the PIPE 1 parent saves prevpipe of the PIPE 1
 ** so the PIPE 2 child can access it
 */

void	ft_pipe(char **cmd, int cmdlen, char **env, int *prevpipe)
{
	int		pipefd[2];
	pid_t	cpid;

	pipe (pipefd);								// Creates a pipe
	cpid = fork ();							// Creates a child

	if (cpid == 0)                       	//	[The Child]
	{

		close (PIPEIN);                  	// Close PIPEIN

		dup2 (*prevpipe, STDIN_FILENO);		// Redirect STDIN to STDIN or prevpipe
		close (*prevpipe);

		dup2 (PIPEOUT, STDOUT_FILENO);    	// Redirect STDOUT to PIPEOUT
		close (PIPEOUT);

		cmd[cmdlen] = NULL;					// EXEC
		execve (cmd[0], cmd, env);
	}
	else                                	//	[The Parent]
	{
		close (PIPEOUT);                  	// Close PIPEOUT
		close (*prevpipe);             		// Update prevpipe

		*prevpipe = PIPEIN;
	}
}

/*
 ** @brief
 */

int	main(int ac, char **av, char **env)
{
	(void)ac;
	int	prevpipe;
	int cmdlen;

	cmdlen = 0;
	prevpipe = dup (STDIN_FILENO); // Init prevpipe
	while (av[cmdlen] && av[cmdlen + 1])
	{
		av += cmdlen + 1;
		cmdlen = ft_cmdlen (av);
		if (av[cmdlen] != NULL && *av[cmdlen] == '|')
		{
			dprintf (2, "> PIPED  PROG %s\n", av[0]);
			ft_pipe (av, cmdlen, env, &prevpipe);
		}
		else if (av[cmdlen] == NULL || *av[cmdlen] == ';')
		{
			dprintf (2, "> SINGLE PROG %s\n", av[0]);
			ft_program (av, cmdlen, env, prevpipe);
		}
	}
	return (0);
}
