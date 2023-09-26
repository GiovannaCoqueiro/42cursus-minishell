#include "minishell.h"

static void	child(int *fd, t_exec *exec);
static void	make_cmd(t_exec *exec);
static void	cmd_search(t_exec *exec);

void	pipe_it(t_exec *exec)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		error_check(exec);
	pid = fork();
	if (pid == -1)
		error_check(exec);
	if (pid == 0)
		child(fd, exec);
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		waitpid(pid, NULL, WNOHANG);
	}
}

static void	child(int *fd, t_exec *exec)
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	make_cmd(exec);
}

static void	make_cmd(t_exec *exec)
{
	struct stat	file_info;

	if (stat(exec->cmd[0], &file_info) == 0)
		if (access(*exec->cmd, X_OK) == 0)
			printf("a\n");
			// if (execve(exec->cmd[0], exec->cmd, exec->env) == -1)
			// 	error_check(exec);
	cmd_search(exec);
}

static void	cmd_search(t_exec *exec)
{
	int		i;
	char	*temp;

	i = -1;
	while (exec->all_paths[++i] != NULL)
	{
		temp = ft_strjoin(exec->all_paths[i], exec->cmd[0]);
		if (access(temp, F_OK) == 0)
		{
			if (access(*exec->cmd, X_OK) == 0)
				printf("b\n");
			// if (execve(temp, exec->cmd, exec->env) == -1)
			// {
			// 	free(temp);
			// 	error_check(exec);
			// }
		}
		free(temp);
	}
	if (exec->all_paths[i] == NULL)
		error_check(exec);
}
