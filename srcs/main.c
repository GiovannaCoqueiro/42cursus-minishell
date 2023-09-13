#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	(void) argv;
	if (argc == 1)
	{
		// signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		data = ft_calloc(1, sizeof(t_data));
		data->path = save_path(envp);
		copy_env(&data->env, envp);
		init_readline(data);
		free_for_all(data);
	}
	return (0);
}

void	copy_env(t_list **list, char **env)
{
	int		i;

	i = -1;
	while (env[++i] != NULL)
		ft_lstadd_back(list, ft_lstnew(env[i]));
}

char	**save_path(char **envp)
{
	char	*start;
	char	**arr;

	arr = NULL;
	while (*envp)
	{
		start = ft_strnstr(*envp, "PATH=", 5);
		if (start != NULL)
		{
			start = ft_strtrim(start, "PATH=");
			arr = ft_split(start, ':');
			break ;
		}
		envp++;
	}
	free(start);
	return (arr);
}

void	init_readline(t_data *data)
{
	while (true)
	{
		data->prompt = readline("$>");
		if (data->prompt == NULL)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (ft_strlen(data->prompt) >= 1)
			add_history(data->prompt);
		read_prompt(data);
		free(data->prompt);
	}
}

void	read_prompt(t_data *data)
{
	if (ft_strncmp(data->prompt, "exit", 4) == 0)
		exit_builtin(data);
	else if (ft_strncmp(data->prompt, "env", 3) == 0)
		env_builtin(data);
	else if (ft_strncmp(data->prompt, "pwd", 3) == 0)
		pwd_builtin();
	else if (ft_strncmp(data->prompt, "unset", 5) == 0)
		unset_builtin(data);
}
