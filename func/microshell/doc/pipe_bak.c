#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#define SUCCESS 0
#define FAILURE 1

void	ft_print_cmd(int cmdlen, char **cmd)
{
	int	j;

	j = -1;
	while (++j < cmdlen)
		dprintf (2, "cmd %i  = %s\n", j, cmd[j]);
	dprintf (2, "cmd %i  = %s\n", j, cmd[j]);
}

int	ft_cmdlen(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && *cmd[len] != '|' && *cmd[len] != ';')
		len++;
	return (len);
}

//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

void	ft_program(char **cmd, int cmdlen, char **env, int fdcpy) // XXX fdcpy
{
	int	pid;

	pid = fork ();

	dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN_FILENO);
	dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT_FILENO);
	dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

	if (pid == 0)
	{

		cmd[cmdlen] = NULL;

		dup2 (fdcpy, STDIN_FILENO);		// XXX Set STDIN to our fdcpy
		close (fdcpy);					// XXX Close fdcpy

		dprintf (2, "child %s: %i: STDIN=%i\n", __func__, __LINE__, STDIN_FILENO);
		dprintf (2, "child %s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT_FILENO);
		dprintf (2, "child %s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

		if (execve (cmd[0], cmd, env) == -1)
			dprintf (2, "Error: EXECVE(2)\n");
	}
	else
	{

		close (fdcpy);					// XXX Close unused fdcpy

		while (wait (NULL) != -1)
			;

		dprintf (2, "paren %s: %i: STDIN=%i\n", __func__, __LINE__, STDIN_FILENO);
		dprintf (2, "paren %s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT_FILENO);
		dprintf (2, "paren %s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

	}
}

int	ft_pipe(char **cmd, int cmdlen, char **env, int *fdcpy)
{
	int	p[2];
	int	pid;

	pipe (p);							// Create a pipe

	dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN_FILENO);
	dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT_FILENO);
	dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, *fdcpy);
	dprintf (2, "%s: %i: p[0]=%i\n", __func__, __LINE__, p[0]);
	dprintf (2, "%s: %i: p[1]=%i\n", __func__, __LINE__, p[1]);

	pid = fork ();						// Create a new process
	if (pid == 0)                       //   [The Child]
	{

		close (p[0]);                  // close unused PIPEIN

		dup2 (p[1], STDOUT_FILENO);    // Set STDOUT to PIPEOUT
		close (p[1]);               	// close PIPEOUT

		/* 'p[1]' fd is copied to STDOUT. */
		/* STDOUT no longer connect to fd 1. */

		// XXX multi pipe case (echo a | cat | grep a)
		dup2 (*fdcpy, STDIN_FILENO);	// Set STDIN to our fdcpy
		close (*fdcpy);					// Close fdcpy

		dprintf (2, "child %s: %i: STDIN=%i\n", __func__, __LINE__, STDIN_FILENO);
		dprintf (2, "child %s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT_FILENO);
		dprintf (2, "child %s: %i: fdcpy=%i\n", __func__, __LINE__, *fdcpy);
		dprintf (2, "child %s: %i: p[0]=%i\n", __func__, __LINE__, p[0]);
		dprintf (2, "child %s: %i: p[1]=%i\n", __func__, __LINE__, p[1]);

		cmd[cmdlen] = NULL;				// Delimit the command with a NULL
		if (execve (cmd[0], cmd, env) == -1)
			dprintf (2, "Error: EXECVE(2)\n");
	}
	else                                //   [The Parent]
	{

		close (p[1]);                  // Close p[1]
		close (*fdcpy);                // Close fdcpy
		*fdcpy = p[0];                // Set fdcpy to p[0]

		dprintf (2, "paren %s: %i: STDIN=%i\n", __func__, __LINE__, STDIN_FILENO);
		dprintf (2, "paren %s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT_FILENO);
		dprintf (2, "paren %s: %i: fdcpy=%i\n", __func__, __LINE__, *fdcpy);
		dprintf (2, "paren %s: %i: p[0]=%i\n", __func__, __LINE__, p[0]);
		dprintf (2, "paren %s: %i: p[1]=%i\n", __func__, __LINE__, p[1]);

	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	int	cmdlen;
	int	fdcpy; // XXX

	(void)ac;
	(void)env;
	cmdlen = 0;
	fdcpy = dup (STDIN_FILENO); // XXX Init

	dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN_FILENO);
	dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT_FILENO);
	dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

	while (av[cmdlen] && av[cmdlen + 1])
	{
		av += cmdlen + 1;
		cmdlen = ft_cmdlen (av);
		if (av[cmdlen] == NULL || *av[cmdlen] == ';')
		{
			dprintf (2, ">PROG<\n");
			ft_program (av, cmdlen, env, fdcpy);
		}
		else if (*av[cmdlen] == '|')
		{
			dprintf (2, ">PIPE<\n");
			ft_pipe (av, cmdlen, env, &fdcpy);
		}
	}
	return (0); }
