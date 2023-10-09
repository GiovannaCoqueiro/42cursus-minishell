#include "minishell.h"

static char	**turn_env_to_arr(t_list *env);
static void	commands_fork(t_args *args, t_data *data);

void	execute(t_data *data, t_exec *exec)
{
	t_args	args;

	args.cmd_count = data->cmd_count;
	args.env = turn_env_to_arr(data->env);
	args.exec = exec;
	data->args = &args;
	args.i = 0;
	pipe(args.pipis);
	pipe(args.pipes);
	commands_fork(&args, data);
	close_pipes(&args);
	ft_free_str_arr(&args.env);
}

static char	**turn_env_to_arr(t_list *env)
{
	char	**arr;
	int		i;

	arr = ft_calloc(sizeof(char *), ft_lstsize(env) + 1);
	i = 0;
	while (env != NULL)
	{
		arr[i] = ft_calloc(sizeof(char), ft_strlen(env->content) + 1);
		ft_strlcpy(arr[i], env->content, ft_strlen(env->content) + 1);
		env = env->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

static void	commands_fork(t_args *args, t_data *data)
{
	pid_t	*pids;
	int		i;

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
