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

int	main(int ac, char **av, char **env)
{
	int		cmdlen;
	int		fdcpy;
	int		p[2];
	pid_t	pid;

	(void)ac;
	(void)env;
	cmdlen = 0;
	fdcpy = dup (STDIN_FILENO); // Init fdcpy
	while (av[cmdlen] && av[cmdlen + 1])
	{
		av += cmdlen + 1;
		cmdlen = ft_cmdlen (av);

		if (av[cmdlen] && *av[cmdlen] == '|')
		{
			dprintf(2, "NOT LAST> %s	%i\n", av[0], cmdlen);
			pipe (p);
			pid = fork ();
			if (pid == 0)                       	//	[The Child]
			{
				close (PIPEIN);                  	// Close PIPEIN
				dup2 (PIPEOUT, STDOUT_FILENO);    	// Redirect STDOUT to PIPEOUT
				close (PIPEOUT);
				dup2 (fdcpy, STDIN_FILENO);			// Redirect STDIN to STDIN or fdcpy
				close (fdcpy);
				av[cmdlen] = NULL;					// EXEC
				execve (av[0], av, env);
			}
			close (PIPEOUT);                  		// Close PIPEOUT
			close (fdcpy);              			// Update fdcpy
			fdcpy = PIPEIN;
		}
		if (av[cmdlen] == NULL || *av[cmdlen] == ';')
		{
			dprintf(2, "    LAST> %s	%i\n", av[0], cmdlen);
			pid = fork ();
			if (pid == 0)
			{
				dup2 (fdcpy, STDIN_FILENO);			// Redirect STDIN to fdcpy
				close (fdcpy);
				av[cmdlen] = NULL;					// EXEC
				execve (av[0], av, env);
			}
			close (fdcpy);							// Close fdcpy
			while (wait (NULL) != -1)
				;
		}
	}
	return (0);
}
