#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

#include <stdlib.h>


# define MAX_PIPES 1080
# define PIPEIN  p[0]
# define PIPEOUT p[1]

int	ft_cmdlen(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && *cmd[len] != '|' && *cmd[len] != ';')
		len++;
	return (len);
}

/*
 ** @brief
 **
 ** the PIPE 1 parent saves prevpin of the PIPE 1
 ** so the PIPE 2 child can access it
 */

// void	ft_pipe(char **cmd, int cmdlen, char **env, int *prevpin)
// {
// 	int		p[2];
// 	pid_t	pid;
//
// 	pipe (p);								// Creates a pipe
// 	pid = fork ();							// Creates a child processes
// 	if (pid == 0)                       	//   [The Child]
// 	{
//
// 		close (PIPEIN);                  	// Close unused PIPEIN
//
// 		dup2 (PIPEOUT, STDOUT_FILENO);    	// Connect PIPEOUT to STDOUT_FILENO
// 		close (PIPEOUT);               		// close PIPEOUT
//
// 		/* 'PIPEOUT' fd is copied to STDOUT. */
// 		/* STDOUT no longer connect to fd 1. */
//
// 		// multi pipe case (echo a | cat | grep a)
// 		dup2 (*prevpin, STDIN_FILENO);		// Connect PIPEIN to STDIN_FILENO
// 		close (*prevpin);					// Close *prevpin
//
// 		cmd[cmdlen] = NULL;					// Delimit the command with a NULL
// 		if (execve (cmd[0], cmd, env) == -1)
// 			dprintf (2, "Error: EXECVE(2)\n");
// 	}
// 	else                                	//   [The Parent]
// 	{
// 		close (PIPEOUT);                  	// Close PIPEOUT
// 		close (*prevpin);                	// Close *prevpin
// 		*prevpin = PIPEIN;                	// Set *prevpin to PIPEIN
// 	}
// }

int ft_pipe(char **av, char **env)
{
	int fdcpy = dup (STDIN_FILENO);
	int pipes[MAX_PIPES][2];
	int num_pipes = 0;
	int cmdlen = 0;

	while (av[cmdlen] && av[cmdlen + 1])
	{
		pipe(pipes[num_pipes]);

		av += cmdlen + 1;
		cmdlen = ft_cmdlen (av);

		pid_t pid = fork();
		if (pid == 0) // CHILD 1
		{
			if (av[cmdlen] && *av[cmdlen] == '|')
			{
				dprintf(2, "NOT LAST> %s	%i\n", av[0], cmdlen);

				dup2(pipes[num_pipes][1], 1);
				close(pipes[num_pipes][0]);

				dup2 (fdcpy, STDIN_FILENO); // Redirect STDIN to STDIN or fdcpy
				close (fdcpy);

				av[cmdlen] = NULL;
				execve (av[0], av, env);
			}
		}
		else
		{
			dprintf (2, "C\n");
			pid_t pid2 = fork();
			if (pid2 == 0) // CHILD 2
			{
				if (av[cmdlen] == NULL || *av[cmdlen] == ';')
				{
					dprintf(2, "NOT FIRST> %s	%i\n", av[0], cmdlen);

					dup2(pipes[num_pipes][0], 0);
					close(pipes[num_pipes][1]);

					av[cmdlen] = NULL;
					execve (av[0], av, env);
				}
			}
		}
		num_pipes++;
	}
	return (1);
}


/*
j** @brief
 */

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)env;
	ft_pipe (av, env);
	return (0);
}

