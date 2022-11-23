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

	dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
	dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
	dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

	if (pid == 0)
	{

		dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
		dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
		dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

		cmd[cmdlen] = NULL;

		dup2 (fdcpy, STDIN_FILENO);		// XXX Set STDIN to our fdcpy
		close (fdcpy);					// XXX Close fdcpy

		dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
		dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
		dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

		if (execve (cmd[0], cmd, env) == -1)
			dprintf (2, "Error: EXECVE(2)\n");
	}
	else
	{
		dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
		dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
		dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);


		close (fdcpy);					// XXX Close unused fdcpy

		while (wait (NULL) != -1)
			;

		dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
		dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
		dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

	}

	dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
	dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
	dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

}

int	ft_pipe(char **cmd, int cmdlen, char **env, int *fdcpy)
{
	int	fd[2];
	int	pid;

	pipe (fd);							// Create a pipe

	dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
	dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
	dprintf (2, "%s: %i: fd[0]=%i\n", __func__, __LINE__, fd[0]);
	dprintf (2, "%s: %i: fd[1]=%i\n", __func__, __LINE__, fd[1]);
	dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

	pid = fork ();						// Create a new process
	if (pid == 0)                       //   [The Child]
	{
		dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
		dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
		dprintf (2, "%s: %i: fd[0]=%i\n", __func__, __LINE__, fd[0]);
		dprintf (2, "%s: %i: fd[1]=%i\n", __func__, __LINE__, fd[1]);
		dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

		close (fd[0]);                  // close unused PIPEIN

		dup2 (fd[1], STDOUT_FILENO);    // Set STDOUT to PIPEOUT
		close (fd[1]);               	// close PIPEOUT

		/* 'fd[1]' fd is copied to STDOUT. */
		/* STDOUT no longer connect to fd 1. */

		dup2 (*fdcpy, STDIN_FILENO);	// Set STDIN to our fdcpy
		close (*fdcpy);					// Close fdcpy

		dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
		dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
		dprintf (2, "%s: %i: fd[0]=%i\n", __func__, __LINE__, fd[0]);
		dprintf (2, "%s: %i: fd[1]=%i\n", __func__, __LINE__, fd[1]);
		dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

		cmd[cmdlen] = NULL;				// Delimit the command with a NULL
		if (execve (cmd[0], cmd, env) == -1)
			dprintf (2, "Error: EXECVE(2)\n");
	}
	else                                //   [The Parent]
	{

		dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
		dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
		dprintf (2, "%s: %i: fd[0]=%i\n", __func__, __LINE__, fd[0]);
		dprintf (2, "%s: %i: fd[1]=%i\n", __func__, __LINE__, fd[1]);
		dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

		close (fd[1]);                  // Close fd[1]
		close (*fdcpy);                // Close fdcpy
		*fdcpy = fd[0];                // Set fdcpy to fd[0]

		dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
		dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
		dprintf (2, "%s: %i: fd[0]=%i\n", __func__, __LINE__, fd[0]);
		dprintf (2, "%s: %i: fd[1]=%i\n", __func__, __LINE__, fd[1]);
		dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

	}

	dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
	dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
	dprintf (2, "%s: %i: fd[0]=%i\n", __func__, __LINE__, fd[0]);
	dprintf (2, "%s: %i: fd[1]=%i\n", __func__, __LINE__, fd[1]);
	dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);

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
	dprintf (2, "%s: %i: STDIN=%i\n", __func__, __LINE__, STDIN);
	dprintf (2, "%s: %i: STDOUT=%i\n", __func__, __LINE__, STDOUT);
	dprintf (2, "%s: %i: fdcpy=%i\n", __func__, __LINE__, fdcpy);
	while (av[cmdlen] && av[cmdlen + 1])
	{
		av += cmdlen + 1;
		cmdlen = ft_cmdlen (av);
		if (av[cmdlen] == NULL || *av[cmdlen] == ';')
		{
			dprintf (2, ">PRG<\n");
			ft_program (av, cmdlen, env, fdcpy);
		}
		else if (*av[cmdlen] == '|')
		{
			dprintf (2, ">PIPE<\n");
			ft_pipe (av, cmdlen, env, &fdcpy);
		}
	}
	return (0);
}
