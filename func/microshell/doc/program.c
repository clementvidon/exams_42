#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 ** @brief      Return the length of the pointed command line
 */

int	ft_cmdlen(char **cmd)
{
	int	len;

	len = 0;
	while (cmd[len] && *cmd[len] != '|' && *cmd[len] != ';')
		len++;
	return (len);
}

/*
 ** @brief      Handle program exec
 **
 ** - creates a process dedicated to the execution
 ** - lock the end of the command with a NULL termination
 ** - execute
 */

void	ft_program(char **cmd, int cmdlen, char **env)
{
	int	pid;

	pid = fork ();
	if (pid == 0)
	{
		cmd[cmdlen] = NULL;
		if (execve (cmd[0], cmd, env) == -1)
			dprintf (2, "Error: EXECVE(2)\n");
	}
	else
	{
		while (wait (NULL) != -1)
			;
	}
}

/*
 ** @brief      Main
 **
 ** ./a.out /bin/echo "(:" ";" /bin/echo ":)"
 */

int	main(int ac, char **av, char **env)
{
	int	cmdlen;

	(void)ac;
	cmdlen = 0;
	while (av[cmdlen] && av[cmdlen + 1])
	{
		av += cmdlen + 1;
		cmdlen = ft_cmdlen (av);
		if (!strcmp (av[0], "cd"))
			dprintf (2, "CD\n");
		else if (av[cmdlen] == NULL || *av[cmdlen] == ';')
		{
			dprintf (2, "PRG\n");
			ft_program (av, cmdlen, env);
		}
		else if (*av[cmdlen] == '|')
			dprintf (2, "PIPE\n");
	}
	return (0);
}

