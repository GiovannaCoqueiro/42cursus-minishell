#include "minishell.h"

static char	**find_path(char **env);
static void	try_paths(t_args *args, char **path);

void	child_process(t_data *data, pid_t *pids)
{
	char	**path;

	path = find_path(data->args->env);
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
	try_paths(data->args, path);
	ft_putstr_fd("gibi: command not found\n", 2);
	free_cmd_not_found(path, data->args->env, data, pids);
	exit(127);
}

static char	**find_path(char **env)
{
	int		i;
	char	**temp;
	char	**paths;

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
