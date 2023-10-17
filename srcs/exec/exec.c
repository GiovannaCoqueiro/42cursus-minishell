#include "minishell.h"

static void	commands_fork(t_args *args, t_data *data);
static void	wait_all_processes(t_data *data, pid_t *pids, int flag);

void	execute(t_data *data)
{
	t_args	args;

	data->args = &args;
	args.index = 0;
	pipe(args.pipis);
	pipe(args.pipes);
	commands_fork(&args, data);
	close_pipes(&args);
}

static void	commands_fork(t_args *args, t_data *data)
{
	pid_t	*pids;
	int		i;
	t_list	*temp;

	i = 0;
	temp = data->token;
	pids = ft_calloc(sizeof(int), data->process_count);
	while (args->index < data->process_count)
	{
		if (data->lexer[i] == PIPE)
		{
			i++;
			temp = temp->next;
		}
		pids[args->index] = fork();
		if (pids[args->index] == 0)
			child_process(data, temp, &data->lexer[i], pids);
		if (data->process_count == 1)
			wait_all_processes(data, pids, data->process_count);
		recycle_pipe(args);
		while (temp != NULL && data->lexer[i] != PIPE)
		{
			temp = temp->next;
			i++;
		}
		args->index++;
	}
	wait_all_processes(data, pids, data->process_count);
	free(pids);
}

static void	wait_all_processes(t_data *data, pid_t *pids, int flag)
{
	int	i;

	i = -1;
	if (flag == 1)
	{
		waitpid(pids[++i], &data->exit_status, 0);
		if (WEXITSTATUS(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
	else
	{
		while (++i < data->process_count)
			waitpid(pids[i], &data->exit_status, 0);
		if (WEXITSTATUS(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
}

void	execute_builtin(t_data *data, t_exec *exec, pid_t *pids)
{
	if (ft_strcmp(data->exec->cmd[0], "env") == 0)
		env_builtin(data, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "pwd") == 0)
		pwd_builtin(data);
	else if (ft_strcmp(data->exec->cmd[0], "export") == 0)
		export_builtin(data, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "unset") == 0)
		unset_builtin(data, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "exit") == 0)
		exit_builtin(data, pids, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "echo") == 0)
		echo_builtin(data, exec->cmd);
	else if (ft_strcmp(data->exec->cmd[0], "cd") == 0)
		cd_builtin(data, exec->cmd);
}
