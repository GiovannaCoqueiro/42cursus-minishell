#include "minishell.h"

static void	commands_fork(t_args *args, t_data *data);
static void	wait_all_processes(t_data *data, pid_t *pids);

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

	i = 0;
	pids = ft_calloc(sizeof(int), data->process_count);
	while (args->index < data->process_count)
	{
		if (data->lexer[i] == PIPE)
		{
			i++;
			data->token = data->token->next;
		}
		pids[args->index] = fork();
		if (pids[args->index] == 0)
			child_process(data, data->token, &data->lexer[i], pids);
		// if (data->process_count == 1)
		// 	wait(NULL);
		// recycle_pipe(args);
		while (data->token != NULL && data->lexer[i] != PIPE)
		{
			data->token = data->token->next;
			i++;
		}
		args->index++;
	}
	wait_all_processes(data, pids);
	free(pids);
	// if (args->exec->lex == BUILTIN && data->process_count == 1)
	// 	execute_builtin(data, args->exec, NULL);
	// else
	// {
	// 	pids = ft_calloc(sizeof(int), args->cmd_count);
	// 	while (args->index < data->process_count)
	// 	{
	// 		pids[args->index] = fork();
	// 		if (pids[args->index] == 0)
	// 			child_process(data, pids);
	// 		if (args->cmd_count == 1)
	// 			wait(NULL);
	// 		recycle_pipe(args);
	// 		args->index++;
	// 		args->exec = args->exec->next;
	// 	}
	// 	wait_all_processes(args, pids);
	// 	free(pids);
	// }
}

static void	wait_all_processes(t_data *data, pid_t *pids)
{
	int	i;

	i = -1;
	while (++i < data->process_count)
		waitpid(pids[i], &data->exit_status, 0);
}

void	execute_builtin(t_data *data, t_exec *exec, pid_t *pids)
{
	if (ft_strcmp(data->args->exec->cmd[0], "env") == 0)
		env_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "pwd") == 0)
		pwd_builtin(data);
	else if (ft_strcmp(data->args->exec->cmd[0], "export") == 0)
		export_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "unset") == 0)
		unset_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "exit") == 0)
		exit_builtin(data, pids, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "echo") == 0)
		echo_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "cd") == 0)
		cd_builtin(data, exec->cmd);
}
