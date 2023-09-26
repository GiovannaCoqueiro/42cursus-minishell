#include "minishell.h"

static char	**turn_env_to_arr(t_list *env);
static void	take_paths(char **env, t_exec *exec);
// static int	open_file(char *file, int mode, t_exec *exec);

void	prepare_exec(t_list *token, int len, t_data *data)
{
	int		i;
	t_exec	exec;

	exec.cmd = ft_calloc(sizeof(char *), len + 1);
	i = -1;
	while (++i < len)
	{
		exec.cmd[i] = ft_calloc(sizeof(char), ft_strlen(token->content) + 1);
		ft_strlcpy(exec.cmd[i], token->content, ft_strlen(token->content) + 1);
		token = token->next;
	}
	exec.cmd[i] = NULL;
	exec.env = turn_env_to_arr(data->env);
	execute(&exec);
}

void	execute(t_exec *exec)
{
	take_paths(exec->env, exec);
	pipe_it(exec);
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

static void	take_paths(char **env, t_exec *exec)
{
	int		i;
	char	**temp;

	i = 0;
	while (env[i] != NULL && ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	temp = ft_split(&env[i][5], ':');
	i = 0;
	while (temp[i] != NULL)
		i++;
	exec->all_paths = malloc(sizeof(char *) * (i + 1));
	if (exec->all_paths == NULL)
	{
		ft_free_str_arr(temp);
		exit(1);
	}
	i = -1;
	while (temp[++i] != NULL)
		exec->all_paths[i] = ft_strjoin(temp[i], "/");
	exec->all_paths[i] = NULL;
	ft_free_str_arr(temp);
}

// static int	open_file(char *file, int mode, t_exec *exec)
// {
// 	int	fd;

// 	if (mode == 1)
// 		fd = open(file, O_RDONLY);
// 	else if (mode == 2)
// 		fd = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0777);
// 	else
// 		fd = open(file, O_APPEND | O_CREAT | O_WRONLY, 0777);
// 	if (fd == -1)
// 	{
// 		if (mode == 2)
// 			close(exec->infile);
// 		perror("Error");
// 		exit(1);
// 	}
// 	return (fd);
// }

