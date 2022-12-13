#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

# define MAX_PIPES FOPEN_MAX
# define PIPEIN  p[0]
# define PIPEOUT p[1]

// just count number of commands
int ft_count_cmd(char ***cmd) {
	int i;
	i = 0;
	while (cmd[i]) i++;
	return i;
}

void ft_pipe(char ***cmd)
{
	int i;
	int j = 0;
	pid_t pid;
	int cmdlen = ft_count_cmd(cmd);
	int pipes[MAX_PIPES];

	i = -1; // Create all the pipes needed
	while (++i < cmdlen)
		pipe(pipes + i * 2);
	while (*cmd != NULL)
	{
		pid = fork();
		if (pid == 0)
		{
			if (*(cmd + 1) != NULL) // if not last
				dup2(pipes[j + 1], 1);
			if (j != 0) // if not first
				dup2(pipes[j - 2], 0);
			i = -1; // close parents fds
			while (++i < 2 * cmdlen)
				close(pipes[i]);
			execvp((*cmd)[0], *cmd);
		}
		cmd++;
		j += 2;
	}
	i = -1; // close parents fds
	while (++i < 2 * cmdlen)
		close(pipes[i]);
	i = -1; // wait
	while (++i < cmdlen)
		wait(NULL);
}


int main(int argc, char *argv[]) {
	(void)argv;
	(void)argc;
	char *echo[] = {"echo", "salut", NULL};
	char *wc[] = {"wc", NULL};
	char *cate[] = {"cat", "-e", NULL};
	(void)echo;
	(void)wc;
	(void)cate;

	char **cmd[] = {echo, wc, wc, NULL};

	ft_pipe(cmd);
	return (0);
}

