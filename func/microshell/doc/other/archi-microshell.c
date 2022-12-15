#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_fatal(void)
{
	write (2, "error: fatal\n", 13);
	exit (1);
}

void	nop(void)
{
	dprintf (2, "nop\n");
	exit (1);
}
void	error_printer(char *error, char *argument)
{
	write(2, error, ft_strlen(error));
	if (argument)
	{
		write(2, " ", 1);
		write(2, argument, ft_strlen(argument));
	}
	write(2, "\n", 1);
}

void	ft_cd(char **args)
{
	if (!args[1] || args[2])
		error_printer("error: cd: bad arguments", NULL);
	else if (chdir(args[1]) == -1)
		error_printer("error: cd: cannot change directory to", args[1]);
}

void	exec(char **argv, int is_piped, int old_stdin, char **env)
{
	int	fd[2];
	int	pid;

	if (strcmp(argv[0], "cd") == 0)
	{
		ft_cd(argv);
		return ;
	}
	if (is_piped && pipe(fd) == -1)
	{
		error_printer("error: fatal", NULL);
		if (close(old_stdin) == -1)
			ft_fatal ();
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		error_printer("error: fatal", NULL);
		if (close(old_stdin) == -1)
			ft_fatal ();
		exit(1);
	}
	if (pid == 0)
	{
		if (is_piped)
		{
			if (close(fd[0]) == -1)
				ft_fatal ();
			dup2(fd[1], 1);
			if (close(fd[1]) == -1)
				ft_fatal ();
		}
		execve(argv[0], argv, env);
		error_printer("error: cannot execute", argv[0]);
		if (close(old_stdin) == -1)
			ft_fatal ();
		exit(1);
	}
	else
	{
		if (is_piped)
		{
			if (close(fd[1]) == -1)
				ft_fatal ();
			dup2(fd[0], 0);
			if (close (fd[0]) == -1)
				ft_fatal ();
		}
		else
			dup2(old_stdin, 0);
		waitpid(pid, 0, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	int	is_piped = 0;
	int	old_stdin = dup(0);
	int	i = 1;
	int j = 1;

	(void)argc;
	while(argv[i])
	{
		if (strcmp(argv[i], "|") == 0 || strcmp(argv[i], ";") == 0)
		{
			if (strcmp(argv[i], "|") == 0)
				is_piped = 1;
			argv[i] = NULL;
			if (argv[j])
				exec(argv + j, is_piped, old_stdin, env);
			is_piped = 0;
			j = i + 1;
		}
		else if (argv[i + 1] == NULL)
			exec(argv + j, is_piped, old_stdin, env);
		i++;
	}
	if (close(old_stdin) == -1)
		ft_fatal ();
	return (0);
}
