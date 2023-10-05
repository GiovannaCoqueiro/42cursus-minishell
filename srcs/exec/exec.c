#include "minishell.h"

static char	**turn_env_to_arr(t_list *env);
static void	commands_fork(t_args *args, t_data *data);
static char	**find_path(char **env);
static void	try_paths(t_args *args);

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
	ft_free_str_arr(args.env);
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
	int 	i;

	pids = ft_calloc(sizeof(int), args->cmd_count);
	while (args->i < args->cmd_count)
	{
		pids[args->i] = fork();
		if (pids[args->i] == 0)
		{
			args->path = find_path(args->env);
			if (args->cmd_count > 1)
			{
				if (args->i == args->cmd_count - 1)
					last_command(args);
				else if (args->i == 0)
					first_command(args);
				else
					middle_command(args);
			}
			close_pipes(args);
			try_paths(args);
			ft_free_str_arr(args->path);
			ft_putstr_fd("pipex: command not found\n", 2);
			free(pids);
			free_for_all(data);
			exit(errno);
		}
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

static char	**find_path(char **env)
{
	char	*start;
	char	**arr;

	arr = NULL;
	while (*env)
	{
		start = ft_strnstr(*env, "PATH=", 5);
		if (start != NULL)
		{
			start = ft_strtrim(start, "PATH=");
			arr = ft_split(start, ':');
			break ;
		}
		env++;
	}
	free(start);
	return (arr);
}

static void	try_paths(t_args *args)
{
	int		i;
	int		strlen;
	char	*copy;

	if (access(args->exec->cmd[0], F_OK) == 0)
		execve(args->exec->cmd[0], args->exec->cmd, args->env);
	i = 0;
	while (args->path[i])
	{
		strlen = ft_strlen(args->path[i]) + ft_strlen(args->exec->cmd[0]) + 2;
		copy = ft_calloc(strlen, sizeof(char));
		ft_strlcat(copy, args->path[i], strlen);
		ft_strlcat(copy, "/", strlen);
		ft_strlcat(copy, args->exec->cmd[0], strlen);
		if (access(copy, F_OK) == 0)
			execve(copy, args->exec->cmd, args->env);
		free(copy);
		i++;
	}
}
