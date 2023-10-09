#include "minishell.h"

static char	**turn_env_to_arr(t_list *env);
static char	**find_path(char **env);
static void	try_paths(t_args *args, char **path, char **env);

void	child_process(t_data *data, pid_t *pids)
{
	char	**path;
	char	**env;

	if (data->args->cmd_count > 1)
	{
		if (data->args->i == data->args->cmd_count - 1)
			last_command(data->args);
		else if (data->args->i == 0)
			first_command(data->args);
		else
			middle_command(data->args);
	}
	close_pipes(data->args);
	if (data->args->exec->lex == CMD)
	{
		env = turn_env_to_arr(data->env);
		path = find_path(env);
		try_paths(data->args, path, env);
		ft_putstr_fd("gibi: command not found\n", 2);
		free_cmd_not_found(path, env, data, pids);
		exit(127);
	}
	execute_builtin(data, data->args->exec);
	free_builtin(data, pids);
	exit(0);
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

static char	**find_path(char **env)
{
	int		i;
	char	**temp;
	char	**paths;

	i = 0;
	while (env[i] != NULL && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	if (env[i] == NULL)
		return (NULL);
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

static void	try_paths(t_args *args, char **path, char **env)
{
	int		i;
	int		strlen;
	char	*copy;

	if (access(args->exec->cmd[0], F_OK) == 0)
		execve(args->exec->cmd[0], args->exec->cmd, env);
	i = 0;
	if (path != NULL)
	{
		while (path[i])
		{
			strlen = ft_strlen(path[i]) + ft_strlen(args->exec->cmd[0]) + 1;
			copy = ft_calloc(strlen, sizeof(char));
			ft_strlcat(copy, path[i], strlen);
			ft_strlcat(copy, args->exec->cmd[0], strlen);
			if (access(copy, F_OK) == 0)
				execve(copy, args->exec->cmd, env);
			free(copy);
			i++;
		}
	}
}
