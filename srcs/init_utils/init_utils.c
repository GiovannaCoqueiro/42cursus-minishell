#include "minishell.h"

t_exec	*create_cmd_arr(t_list *token, int len);
void		exec_addback(t_exec **exec, t_exec *node);

void	copy_env(t_list **list, char **env, t_data *data)
{
	int	i;

	i = -1;
	while (env[++i] != NULL)
	{
		ft_lstadd_back(list, ft_lstnew(ft_strdup(env[i])));
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
		{
			data->home = ft_calloc(1, ft_strlen(&env[i][5]) + 1);
			ft_strlcpy(data->home, &env[i][5], ft_strlen(&env[i][5]) + 1);
		}
	}
}

void	init_readline(t_data *data)
{
	while (true)
	{
		data->token = NULL;
		data->lexer = NULL;
		data->prompt = readline("\033[1;35mgibi>\033[0m ");
		if (data->prompt == NULL)
		{
			ft_putendl_fd("exit", 1);
			break ;
		}
		if (ft_strlen(data->prompt) >= 1)
		{
			add_history(data->prompt);
			if (tokenization(data) == 1 && check_for_quotes(data->token) == 1)
			{
				check_var(data->token, data->env, data);
				read_prompt(data->token, data->lexer, data);
			}
			if (data->lexer != NULL)
				free(data->lexer);
			if (data->token != NULL)
				free_list(data->token);
		}
		free(data->prompt);
	}
}

void	read_prompt(t_list *token, int *lexer, t_data *data)
{
	int		i;
	int		buffer;
	int		list_len;
	t_list	*temp;

	list_len = ft_lstsize(token);
	i = 0;
	data->exec = ft_calloc(1, sizeof(t_exec));
	data->cmd_count = 0;
	temp = token;
	while (i < list_len)
	{
		if (lexer[i] == CMD || lexer[i] == BUILTIN)
		{
			data->cmd_count++;
			buffer = i;
			i++;
			while (i < list_len && lexer[i] == ARG)
				i++;
			exec_addback(&data->exec, create_cmd_arr(token, i - buffer));
			i--;
			while (buffer++ < i)
				token = token->next;
		}
		token = token->next;
		i++;
	}
	// t_exec *test = data->exec;
	// while (test != NULL)
	// {
	// 	int j = -1;
	// 	while (test->cmd[++j] != NULL)
	// 		printf("%s\n", test->cmd[j]);
	// 	test = test->next;
	// }
	execute(data, data->exec);
}

t_exec	*create_cmd_arr(t_list *token, int len)
{
	t_exec	*exec;
	int		i;

	exec = ft_calloc(sizeof(t_exec), 1);
	exec->cmd = ft_calloc(sizeof(char *), len + 1);
	i = -1;
	while (++i < len)
	{
		exec->cmd[i] = ft_calloc(sizeof(char), ft_strlen(token->content) + 1);
		ft_strlcpy(exec->cmd[i], token->content, ft_strlen(token->content) + 1);
		token = token->next;
	}
	exec->cmd[i] = NULL;
	return (exec);
}

void	exec_addback(t_exec **exec, t_exec *node)
{
	t_exec	*temp;

	temp = *exec;
	if (temp->cmd == NULL)
		*exec = node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}
