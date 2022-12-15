#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include <stdio.h>

#define SUCCESS 0
#define FAILURE 1

/* TODO PROTECT SYSCALL */

/*
 ** gcc microshell.c && ./a.out /bin/cat "|" /bin/cat "|" /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello
 ** gcc microshell.c && ./a.out /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello ";" /bin/pwd ";" cd .. ";" /bin/pwd
 ** gcc microshell.c -g -fsanitize=address && ./a.out /bin/cat "|" /bin/cat "|" /bin/ls
 */

/*
 ** @brief      Print an error message.
 **
 ** @param[in]  str the error message
 ** @param[in]  arg what causes the problem
 */

void	ft_puterr(char *issue, char *cause)
{
	while (*issue)
		write (2, issue++, 1);
	if (cause)
		while (*cause)
			write (2, cause++, 1);
	write (2, "\n", 1);
}

/*
 ** @brief      Count command size in term of tokens
 **
 ** @param[in]  cmd a shell command
 ** @return     the number of tokens that compose the given command
 */

int	ft_command_size(char **cmd)
{
	int	count;

	count = 0;
	while (cmd[count] && *cmd[count] != ';' && *cmd[count] != '|')
		count++;
	return (count);
}

/*
 ** @brief      Change directory
 **
 ** @param[in]  cmd a ';', '|' or '\0' terminated command
 ** @return     Success of failure.
 */

int	ft_cd(char **cmd)
{
	if (ft_command_size (cmd) != 2)
	{
		ft_puterr ("error: cd: bad ", "arguments");
		return (FAILURE);
	}
	else if (chdir (cmd[1]) == -1)
	{
		ft_puterr ("error: cd: cannot change directory to ", cmd[1]);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
 ** @brief      Execute a program
 */

int	ft_exec(char **cmd, char **env, int fd_cpy)
{
	dup2 (fd_cpy, STDIN_FILENO);					// Set STDIN to our fd_cpy
	close (fd_cpy);									// Close fd_cpy
	if (execve (cmd[0], cmd, env) == -1)			// Execute
	{
		ft_puterr ("error: cannot execute ", cmd[0]);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
 ** @brief      Handle a command with a program
 */

int	ft_program(char **cmd, int i, char **env, int fd_cpy)
{
	int	pid;

	pid = fork ();									// Creates a new process

	if (pid == 0)									//   [ The Child ]
	{
		cmd[i] = NULL;
		if (ft_exec (cmd, env, fd_cpy))				// Execute
			return (FAILURE);
	}
	else											//   [ The Parent ]
	{
		close (fd_cpy);								// Close unused fd_cpy
		while (wait (NULL) != -1)					// Wait for the child to finish
			;
	}
	return (SUCCESS);
}

/*
 ** @brief      Handle a command with a pipe
 **
 ** @param[in]  cmd a pointer to the current command
 ** @param[in]  i the command number of tokens
 ** @param[in]  env
 ** @param[i/o] fd_cpy
 ** @return     Success or failure.
 */

int	ft_pipe(char **cmd, int i, char **env, int *fd_cpy)
{
	int	fd[2];
	int	pid;

	pipe (fd);										// Create a pipe
	pid = fork ();									// Create a new process
	if (pid == 0)									//   [The Child]
	{
		dup2 (fd[1], STDOUT_FILENO);				// Set STDOUT to PIPEOUT
		close (fd[0]);								// close unused PIPEIN
		close (fd[1]);								// close PIPEOUT
		cmd[i] = NULL;
		if (ft_exec (cmd, env, *fd_cpy))
			return (FAILURE);
	}
	else											//   [The Parent]
	{
		close (fd[1]);								// Close fd[1]
		close (*fd_cpy);							// Close fd_cpy
		*fd_cpy = fd[0];							// Set fd_cpy to fd[0]
	}
	return (SUCCESS);
}

/*
 ** @brief      Microshell
 **
 ** Usage:
 ** ./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello
 ** ./microshell /bin/pwd ";" cd .. ";" /bin/pwd
 **
 ** - One command read per while loop.
 ** - Each command is ';', '|' or '\0' terminated.
 **
 ** - First command starts right after the executable name.
 ** - Next commands start right after their preceding  ';' or '|'.
 **
 ** @param[in]  cmd one or multiple commands
 ** @param[in]  env the parent shell environment
 ** @return     Success of failure.
 */

int	main(int ac, char **cmd, char **env)
{
	int	i;
	int	fd_cpy;

	(void)ac;
	i = 0;
	fd_cpy = dup (STDIN_FILENO); // Init fd_cpy (with any valid fd)
	while (cmd[i] && cmd[i + 1])
	{
		cmd += i + 1;

		i = ft_command_size (cmd);

		if (i && !strcmp (cmd[0], "cd"))
		{
			if (ft_cd (cmd) == FAILURE)
				return (FAILURE);
		}
		// Last program of a command
		else if (i && (cmd[i] == NULL || *cmd[i] == ';'))
		{
			if (ft_program (cmd, i, env, fd_cpy) == FAILURE)
				return (FAILURE);
		}
		// Program followed by a one pipe
		else if (i && *cmd[i] == '|')
		{
			if (ft_pipe (cmd, i, env, &fd_cpy) == FAILURE)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}
