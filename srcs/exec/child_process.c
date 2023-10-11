#include "minishell.h"

 char	**turn_env_to_arr(t_list *env);
 char	**find_path(char **env);
 void	try_paths(t_args *args, char **path, char **env);

void	child_process(t_data *data, t_list *token, int *lexer, pid_t *pids)
{
	char	**path;
	char	**env;
	t_exec	exec;
	int		fd[2];

	(void)pids;
	if (validate_files(token, lexer, &fd[0], &fd[1]) == 1)
	{
		printf("valido\n");
		data->has_cmd = 0;
		exec.cmd = NULL;
		data->exec = &exec;
		get_cmd_and_args(token, lexer, data);
		if (data->process_count > 0)
		{
			if (data->args->index == data->process_count - 1)
				last_command(data->args);
			else if (data->args->index == 0)
				first_command(data->args);
			else
				middle_command(data->args);
		}
		close_pipes(data->args);
		if (data->exec->lex == CMD)
		{
			env = turn_env_to_arr(data->env);
			path = find_path(env);
			try_paths(data->args, path, env);
			free_cmd_not_found(path, env, data, pids);
			exit(127);
		}
		execute_builtin(data, data->args->exec, pids);
		free_builtin(data, pids);
		exit(data->exit_status);
		exit (0);
	}
	printf("não valido\n");
	exit (1);
}

 char	**turn_env_to_arr(t_list *env)
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

 char	**find_path(char **env)
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

 void	try_paths(t_args *args, char **path, char **env)
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
