#include "minishell.h"

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
		data->prompt = readline("$> ");
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
			free(data->lexer);
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

	i = 0;
	list_len = ft_lstsize(token);
	while (i < list_len)
	{
		if (lexer[i] == CMD)
		{
			buffer = i;
			i++;
			while (i < list_len && lexer[i] == ARG)
				i++;
			prepare_exec(token, i - buffer, data);
			i--;
			while (buffer++ < i)
				token = token->next;
		}
		token = token->next;
		i++;
	}
}
