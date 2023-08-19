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
 ** @brief      Count command length in term of tokens
 **
 ** @param[in]  cmd a shell command
 ** @return     the number of tokens that compose the given command
 */

int	ft_command_len(char **cmd)
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

int	ft_builtin_cd(char **cmd)
{
	if (ft_command_len (cmd) != 2)
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

int	ft_exec(char **cmd, int cmdlen, char **env, int fd_cpy)
{
	cmd[cmdlen] = NULL;								// Set command end to NULL so we can pass it to execve.
	dup2 (fd_cpy, STDIN_FILENO);					// Set STDIN_FILENO to fd_cpy
	close (fd_cpy);									// Close fd_cpy
	if (execve (cmd[0], cmd, env) == -1)			// Execute the program
	{
		ft_puterr ("error: cannot execute ", cmd[0]);
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
 ** @brief      Handle a command with a program
 */

int	ft_program(char **cmd, int cmdlen, char **env, int fd_cpy)
{
	int	pid;

	pid = fork ();									// Creates a new process
	if (pid == 0)									//   [The Child]
	{
		if (ft_exec (cmd, cmdlen, env, fd_cpy))	// Execute the program
			return (FAILURE);
	}
	else											//   [The Parent]
	{
		close (fd_cpy);								// Close fd_cpy
		while (wait (NULL) != -1)					// Wait for the child to finish
			;
	//fd_cpy = dup (STDIN_FILENO);				// Set fd_cpy to any valid fd
	}												// XXX useless?
	//close (fd_cpy);									// Close fd_cpy
	return (SUCCESS);
}

/*
 ** @brief      Handle a command with a pipe
 **
 ** @param[in]  cmd a shell command TODO TOUTE MES COMMANDES (check, might be partout)
 ** @param[in]  cmdlen the shell command number of arguments TODO maybe the index of the command averifier
 ** @param[in]  env
 ** @param[i/o] fd_cpy
 ** @return     Success or failure.
 */

int	ft_pipe(char **cmd, int cmdlen, char **env, int *fd_cpy)
{
	int	fd[2];
	int	pid;

	pipe (fd);										// Create a pipe
	pid = fork ();									// Create a new process
	if (pid == 0)									//   [The Child]
	{
		dup2 (fd[1], STDOUT_FILENO);				// Set STDOUT_FILENO to fd[1]
		close (fd[0]);								// close fd[0]
		close (fd[1]);								// close fd[1] la sortie de notre pipe() comme on la donne a STDOUT_FILENO
		if (ft_exec (cmd, cmdlen, env, *fd_cpy))
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
 ** - One command per while loop.
 ** - A shell command is a ';', '|' or '\0' terminated string or group of string.
 **
 ** - First command starts right after the executable name
 ** - Next commands start after their preceding  ';' or '|'
 **
 ** @param[in]  cmd one or multiple commands
 ** @param[in]  env the parent shell environment
 ** @return     Success of failure.
 */

int	main(int ac, char **cmd, char **env)
{
	int	cmdlen;
	int	fd_cpy;

	(void)ac;
	cmdlen = 0;
	fd_cpy = dup (STDIN_FILENO); 					// set fd_cpy to any valid fd
	while (cmd[cmdlen] && cmd[cmdlen + 1])
	{
		cmd += cmdlen + 1;
		cmdlen = ft_command_len (cmd);
		if (cmdlen && !strcmp (cmd[0], "cd"))
		{
			if (ft_builtin_cd (cmd) == FAILURE)
				return (FAILURE);
		}
		else if (cmdlen && (cmd[cmdlen] == NULL || *cmd[cmdlen] == ';')) // == uniquement si commande unique sans pipe apres !!!!!!!
		{
			if (ft_program (cmd, cmdlen, env, fd_cpy) == FAILURE)
				return (FAILURE);
		}
		else if (cmdlen && *cmd[cmdlen] == '|') // ex. ls | wc (ls passe ici et wc passe a programme) cat cat ls (cat et cat passse en DEUX fois ici et ls passe au dessus)
		{
			if (ft_pipe (cmd, cmdlen, env, &fd_cpy) == FAILURE)
				return (FAILURE);
		}
	}
	return (SUCCESS);
}
