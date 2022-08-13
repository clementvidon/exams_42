#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>


/*
 ** Usage: ./a.out /bin/ls "|" /usr/bin/grep microshell ";" /bin/echo hello
 */

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		++i;
	return (i);
}

int	ft_error(void)
{
	write(STDERR_FILENO, "error: fatal\n", 13);
	return (1);
}

int	ft_cd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	if (i != 2)
		write(STDERR_FILENO, "error: cd: bad arguments\n", 25);
	else if (chdir(cmd[1]) == -1)
	{
		write(STDERR_FILENO, "error: cd: cannot change directory to ", 38);
		write(STDERR_FILENO, cmd[1], ft_strlen(cmd[1]));
		write(STDERR_FILENO, "\n", 1);
	}
	else
		return (0);
	return (1);
}

void	ft_child_execute_command(char **cmd, char **env)
{
	if (!strcmp(cmd[0], "cd"))
		exit(ft_cd(cmd));
	execve(cmd[0], cmd, env);
	write(STDERR_FILENO, "error: cannot execute ", 22);
	write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}




void	execute_command(char **cmd, char **env)
{
	int	i;
	int	j;
	int	last;
	int	read;
	int	write;
	int	dup_in;
	int	dup_out;
	int	pid;
	int	fd[2];

	j = 0;
	while (cmd[j] && strcmp(cmd[j], "|"))
		++j;
	if (!cmd[j] && !strcmp(cmd[0], "cd"))
	{
		ft_cd(cmd);
		return ;
	}

	read = dup(STDIN_FILENO); if (read == -1) ft_error();

	dup_in = dup(STDIN_FILENO); if (dup_in == -1) ft_error();
	dup_out = dup(STDOUT_FILENO); if (dup_out == -1) ft_error();

	last = 0;
	i = 0;
	j = 0;
	while (!last)
	{
		while (cmd[j] && strcmp(cmd[j], "|"))
			++j;

		if (!cmd[j])
			last = 1;
		cmd[j] = NULL;

		if (pipe(fd) == -1)
			ft_error();

		if (last)
			write = dup_out;
		else
			write = fd[1];

		if (dup2(read, STDIN_FILENO) == -1)
			ft_error();

		close(read);

		if (dup2(write, STDOUT_FILENO) == -1)
			ft_error();

		close(write);

		pid = fork();
		if (pid == -1)
			ft_error();
		if (pid == 0)
			ft_child_execute_command(cmd + i, env);
		else
			read = fd[0];
		i = ++j;
	}




	while (wait(NULL) != -1)
		;
	if (dup2(dup_in, STDIN_FILENO) == -1)
		ft_error();
	close(dup_in);
	close(fd[1]);
	close(read);
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (i < argc)
	{
		while (argv[j] && strcmp(argv[j], ";"))
			j++;
		argv[j] = NULL;

		if (argv[i])
			execute_command(argv + i, env);
		i = ++j;
	}
	return (0);
}
