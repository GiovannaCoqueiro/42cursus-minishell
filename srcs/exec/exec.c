#include "minishell.h"

static void	commands_fork(t_args *args, t_data *data);

void	execute(t_data *data, t_exec *exec)
{
	t_args	args;

	args.cmd_count = data->cmd_count;
	args.exec = exec;
	data->args = &args;
	args.i = 0;
	pipe(args.pipis);
	pipe(args.pipes);
	commands_fork(&args, data);
	close_pipes(&args);
}

static void	commands_fork(t_args *args, t_data *data)
{
	pid_t	*pids;
	int		i;

	if (args->exec->lex == BUILTIN && args->cmd_count == 1)
		execute_builtin(data, args->exec);
	else
	{
		pids = ft_calloc(sizeof(int), args->cmd_count);
		while (args->i < args->cmd_count)
		{
			pids[args->i] = fork();
			if (pids[args->i] == 0)
				child_process(data, pids);
			if (args->cmd_count == 1)
				wait(NULL);
			recycle_pipe(args);
			args->i++;
			args->exec = args->exec->next;
		}
		i = 0;
		while (i < args->cmd_count)
		{
			waitpid(pids[i], NULL, 0);
			i++;
		}
		free(pids);
	}
}

void	execute_builtin(t_data *data, t_exec *exec)
{
	if (ft_strcmp(data->args->exec->cmd[0], "env") == 0)
		env_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "pwd") == 0)
		pwd_builtin();
	else if (ft_strcmp(data->args->exec->cmd[0], "export") == 0)
		export_builtin(data, exec->cmd);
	else if (ft_strcmp(data->args->exec->cmd[0], "unset") == 0)
		unset_builtin(data);
	else if (ft_strcmp(data->args->exec->cmd[0], "exit") == 0)
		exit_builtin(data);
	// if (ft_strcmp(data->args->exec->cmd[0], "echo") == 0)
	// 	echo_builtin(data);
	// if (ft_strcmp(data->args->exec->cmd[0], "cd") == 0)
	// 	cd_builtin(data);
}
