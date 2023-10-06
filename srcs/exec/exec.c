#include "minishell.h"

static char	**turn_env_to_arr(t_list *env);
static void	commands_fork(t_args *args, t_data *data);
static char	**find_path(char **env);
static void	try_paths(t_args *args, char **path);

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
	char	**path;
	int 	i;

	pids = ft_calloc(sizeof(int), args->cmd_count);
	while (args->i < args->cmd_count)
	{
		pids[args->i] = fork();
		if (pids[args->i] == 0)
		{
				path = find_path(args->env);
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
				try_paths(args, path);
				ft_putstr_fd("gibi: command not found\n", 2);
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

char    **find_path(char **env)
{
    int        i;
    char    **temp;
    char    **paths;

    i = 0;
    while (env[i] != NULL && ft_strncmp("PATH=", env[i], 5) != 0)
        i++;
    temp = ft_split(&env[i][5], ':');
    i = 0;
    while (temp[i] != NULL)
        i++;
    paths = ft_calloc(sizeof(char *), (i + 1));
    i = -1;
    while (temp[++i] != NULL)
        paths[i] = ft_strjoin(temp[i], "/");
    paths[i] = NULL;
    ft_free_str_arr(&temp);
    return (paths);
}

static void	try_paths(t_args *args, char **path)
{
	int		i;
	int		strlen;
	char	*copy;

	if (access(args->exec->cmd[0], F_OK) == 0)
		execve(args->exec->cmd[0], args->exec->cmd, args->env);
	i = 0;
	while (path[i])
	{
		strlen = ft_strlen(path[i]) + ft_strlen(args->exec->cmd[0]) + 1;
		copy = ft_calloc(strlen, sizeof(char));
		ft_strlcat(copy, path[i], strlen);
		ft_strlcat(copy, args->exec->cmd[0], strlen);
		if (access(copy, F_OK) == 0)
			execve(copy, args->exec->cmd, args->env);
		free(copy);
		i++;
	}
}
