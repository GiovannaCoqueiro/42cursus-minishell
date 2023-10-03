#include "minishell.h"

// static void	child(int *fd, t_exec *exec);
// static void	cmd_search(t_exec *exec);

// void	pipe_it(t_exec *exec)
// {
// 	int		fd[2];
// 	pid_t	pid;

// 	if (pipe(fd) == -1)
// 		error_check(exec);
// 	pid = fork();
// 	if (pid == -1)
// 		error_check(exec);
// 	if (pid == 0)
// 		child(fd, exec);
// 	else
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[1]);
// 		waitpid(pid, NULL, WNOHANG);
// 	}
// }

// static void	child(int *fd, t_exec *exec)
// {
// 	dup2(fd[1], STDOUT_FILENO);
// 	close(fd[0]);
// 	make_cmd(exec);
// }
