#include "minishell.h"

static char	**turn_env_to_arr(t_list *env);

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

void	execute(t_data *data, t_exec *exec)
{
	t_args	args;

	args.cmd_count = exec->cmd_count;
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

void	commands_fork(t_args *args, t_data *data)
{
	pid_t	*pids;
	int 	i;

	pids = ft_calloc(sizeof(int), args->cmd_count);
	while (args->i <= args->cmd_count - 1)
	{

		pids[args->i] = fork();
		if (pids[args->i] == 0)
		{
			args->path = find_path(args->env);
			if (args->i == args->cmd_count - 1)
				last_command(args);
			else if (args->i == 0)
				first_command(args);
			else
				middle_command(args);
			close_pipes(args);
			make_cmd(args);
			free_str_arrs(args->path);
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
	while(i < args->cmd_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}

void	close_pipes(t_args *args)
{
	close(args->pipis[0]);
	close(args->pipis[1]);
	close(args->pipes[0]);
	close(args->pipes[1]);
}

char	**find_path(char **env)
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
	ft_free_str_arr(temp);
	return (paths);
}

void	make_cmd(t_args *args)
{
	struct stat	file_info;

	if (stat(args->exec->cmd[0], &file_info) == 0)
	{
		if (access(args->exec->cmd[0], X_OK) == 0)
			execve(args->exec->cmd[0], args->exec->cmd, args->env);
	}
	else
		cmd_search(args);
}

void	cmd_search(t_args *args)
{
	int		i;
	char	*temp;

	i = -1;
	while (args->path[++i] != NULL)
	{
		temp = ft_strjoin(args->path[i], args->exec->cmd[0]);
		if (access(temp, F_OK) == 0)
			if (access(temp, X_OK) == 0)
				execve(temp, args->exec->cmd, args->env);
		free(temp);
	}
}

void	try_paths(t_args *args)
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

void	free_str_arrs(char **arr)
{
	int	j;

	j = 0;
	while (arr[j])
	{
		free(arr[j]);
		j++;
	}
	free(arr);
}

void	recycle_pipe(t_args *args)
{
	if (args->i % 2 == 0)
	{
		close(args->pipes[0]);
		close(args->pipes[1]);
		pipe(args->pipes);
	}
	else
	{
		close(args->pipis[0]);
		close(args->pipis[1]);
		pipe(args->pipis);
	}
}

void	first_command(t_args *args)
{
	dup2(args->pipis[1], 1);
}

void	middle_command(t_args *args)
{
	if (args->i % 2 == 0)
	{
		dup2(args->pipes[0], 0);
		dup2(args->pipis[1], 1);
	}
	else
	{
		dup2(args->pipis[0], 0);
		dup2(args->pipes[1], 1);
	}
}

void	last_command(t_args *args)
{
	if (args->i % 2 == 0)
		dup2(args->pipes[0], 0);
	else
		dup2(args->pipis[0], 0);
}
