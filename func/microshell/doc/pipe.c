#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

# define PIPEIN p[0]
# define PIPEOUT p[1]

int	ft_cmdlen(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && *cmd[len] != '|' && *cmd[len] != ';')
		len++;
	return (len);
}

void	ft_program(char **cmd, int cmdlen, char **env, int prevpin)
{
	int	pid;

	pid = fork ();
	if (pid == 0)
	{

		cmd[cmdlen] = NULL;

		dup2 (prevpin, STDIN_FILENO);		// XXX Set STDIN to our prevpin
		close (prevpin);					// XXX Close prevpin
		if (execve (cmd[0], cmd, env) == -1)
			dprintf (2, "Error: EXECVE(2)\n");
	}
	else
	{
		close (prevpin);					// XXX Close unused prevpin
		while (wait (NULL) != -1)
			;
	}
}

/*
 ** @brief
 **
 ** the PIPE 1 parent saves prevpin of the PIPE 1
 ** so the PIPE 2 child can access it
 */

void	ft_pipe(char **cmd, int cmdlen, char **env, int *prevpin)
{
	int		p[2];
	pid_t	pid;

	pipe (p);								// Creates a pipe
	pid = fork ();							// Creates a child processes
	if (pid == 0)                       	//   [The Child]
	{

		close (PIPEIN);                  	// Close unused PIPEIN

		dup2 (PIPEOUT, STDOUT_FILENO);    	// Connect PIPEOUT to STDOUT_FILENO
		close (PIPEOUT);               		// close PIPEOUT

		/* 'PIPEOUT' fd is copied to STDOUT. */
		/* STDOUT no longer connect to fd 1. */

		// multi pipe case (echo a | cat | grep a)
		dup2 (*prevpin, STDIN_FILENO);		// Connect PIPEIN to STDIN_FILENO
		close (*prevpin);					// Close *prevpin

		cmd[cmdlen] = NULL;					// Delimit the command with a NULL
		if (execve (cmd[0], cmd, env) == -1)
			dprintf (2, "Error: EXECVE(2)\n");
	}
	else                                	//   [The Parent]
	{
		close (PIPEOUT);                  	// Close PIPEOUT
		close (*prevpin);                	// Close *prevpin
		*prevpin = PIPEIN;                	// Set *prevpin to PIPEIN
	}
}

/*
 ** @brief
 */

int	main(int ac, char **av, char **env)
{
	int	cmdlen;
	int	prevpin;

	(void)ac;
	(void)env;
	cmdlen = 0;
	prevpin = dup (STDIN_FILENO); // Init prevpin
	while (av[cmdlen] && av[cmdlen + 1])
	{
		av += cmdlen + 1;
		cmdlen = ft_cmdlen (av);
		if (av[cmdlen] == NULL || *av[cmdlen] == ';')
		{
			dprintf (2, ">PROG<\n");
			ft_program (av, cmdlen, env, prevpin);
		}
		else if (*av[cmdlen] == '|')
		{
			dprintf (2, ">PIPE<\n");
			ft_pipe (av, cmdlen, env, &prevpin);
		}
	}
	return (0);
}
