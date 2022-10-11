#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#include <stdio.h>

#define SUCCESS 0
#define FAILURE 1

/*
 ** ./a.out /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello
 ** hello
 ** archi-microshell.c
 ** microshell
 ** microshell_bak.c
 ** microshell.c
 ** shackbei-microshell.c
 */

/* not needed in exam, but necessary if you want to use this tester:
 ** https://github.com/Glagan/42-exam-rank-04/blob/master/microshell/test.sh
 ** #ifdef TEST_SH
 ** # define TEST		1
 ** #else
 ** # define TEST		0
 ** #endif
 */

void	ft_puterr(char *str, char *arg)
{
	while (*str)
		write (2, str++, 1);
	if (arg)
		while (*arg)
			write (2, arg++, 1);
	write (2, "\n", 1);
}

/*
 ** @brief      Count command length in term of tokens
 **
 ** @param[in]  cmd a ';', '|' or '\0' terminated command
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

int	ft_builtin_cd(char **cmd)
{
	if (ft_command_len (cmd) != 2)
	{
		ft_puterr ("error: cd: bad arguments\n", NULL);
		return (FAILURE);
	}
	else if (chdir (cmd[1]) == -1)
	{
		ft_puterr ("error: cd: cannot change directory to ", cmd[1]);
		return (FAILURE);
	}
}

int	ft_exec(char **cmd, int cmdlen, char **env, int stdin_fd)
{
	//overwrite ; or | or NULL whith NULL to use the array as input for execve.
	//we are here in the child so it has no impact in the parent process.
	cmd[cmdlen] = NULL;
	dup2(stdin_fd, STDIN_FILENO);
	close (stdin_fd);
	if (execve (cmd[0], cmd, env) == -1)
	{
		ft_puterr ("error: cannot execute ", cmd[0]);
		return (FAILURE);
	}
}

int	ft_program(char **cmd, int cmdlen, char **env, int stdin_fd)
{
	int	pid;

	pid = fork ();
	if (pid == 0)
	{
		if (ft_exec (cmd, cmdlen, env, stdin_fd))
			return (FAILURE);
		else
		{
			close (stdin_fd);
			while (waitpid (0, 0, 0) != -1)
				;
			stdin_fd = dup (STDIN_FILENO);
		}
	}
	close (stdin_fd);
	return (SUCCESS);
}

int	ft_pipe(char **cmd, int cmdlen, char **env, int *stdin_fd)
{
	int	fd[2];
	int	pid;
	int	i;

	i = 0;
	pipe (fd);
	pid = fork ();
	if (pid == 0)
	{
		i = 1;
		dup2(fd[1], STDOUT_FILENO);
		close (fd[0]);
		close (fd[1]);
		if (ft_exec (cmd, cmdlen, env, *stdin_fd))
			return (FAILURE);
	}
	else
	{
		close (fd[1]);
		close (*stdin_fd);
		*stdin_fd = fd[0];
	}
	if (i ==1) // TODO make sure it is useful, check fds open at exit
	{
		close (fd[0]);
		close (fd[1]);
	}
	return (SUCCESS);
}

/*
 ** gcc microshell && ./a.out /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello ";" /bin/pwd ";" cd .. ";" /bin/pwd
 */

/*
 ** @brief      Microshell
 **
 ** Usage:
 ** ./microshell /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello
 ** ./microshell /bin/pwd ";" cd .. ";" /bin/pwd
 **
 ** - Each while loop covers one command
 ** - A command is ';', '|' or '\0' terminated string or group of string
 **
 ** - The first command starts after the executable name
 ** - The next commands start after their preceding  ';' or '|'
 **
 ** @param[in]  cmd one or multiple ';', '|' or '\0' terminated commands
 ** @param[in]  env the parent shell environment
 */

int	main(int ac, char **cmd, char **env)
{
	int	cmdlen;
	int	stdin_fd;

	cmdlen = 0;
	stdin_fd = dup (STDIN_FILENO);
	while (cmd[cmdlen] && cmd[cmdlen + 1])
	{

		/* First command starts after the executable name */
		/* Next commands start after the last ';' or '|' */

		cmd += cmdlen + 1;

		/* Counts the number of programs in the command. */

		cmdlen = ft_command_len (cmd);

		/* Cd built-in */

		if (cmdlen && !strcmp (cmd[0], "cd"))
		{
			if (ft_builtin_cd (cmd) == FAILURE)
				return (FAILURE);
		}

		/* Program */

		else if (cmdlen && (cmd[cmdlen] == NULL || *cmd[cmdlen] == ';'))
		{
			if (ft_program (cmd, cmdlen, env, stdin_fd) == FAILURE)
				return (FAILURE);
		}

		/* Pipe */

		else if (cmdlen && *cmd[cmdlen] == '|')
		{
			if (ft_pipe (cmd, cmdlen, env, &stdin_fd) == FAILURE)
				return (FAILURE);
		}

	}
	close (stdin_fd); // TODO fix pipe
	// if (TEST)	// not needed in exam, but necessary if you want to use this tester:
	// 	while (1);	// https://github.com/Glagan/42-exam-rank-04/blob/master/microshell/test.sh
	return (SUCCESS);
}
