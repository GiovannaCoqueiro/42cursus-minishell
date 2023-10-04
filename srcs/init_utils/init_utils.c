#include "minishell.h"

static t_exec	*create_cmd_arr(t_list *token, int len);
static void		exec_addback(t_exec **exec, t_exec *node);

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
	t_exec	*exec;

	list_len = ft_lstsize(token);
	i = 0;
	exec = ft_calloc(1, sizeof(t_exec));
	data->exec = exec;
	exec->cmd_count = 0;
	while (i < list_len)
	{
		if (lexer[i] == CMD || lexer[i] == BUILTIN)
		{
			exec->cmd_count++;
			buffer = i;
			i++;
			while (i < list_len && lexer[i] == ARG)
				i++;
			exec_addback(&exec, create_cmd_arr(token, i - buffer));
			i--;
			while (buffer++ < i)
				token = token->next;
		}
		token = token->next;
		i++;
	}
	execute(data, data->exec);
	// int fd[2];
	// if (pipe(fd) == -1)
	// 	error_check(exec, data);
	// prepare_exec(data);
	// while (cmd_count > 0)
	// {
	// 	open_pipe(fd, exec, data, cmd_count);
	// 	cmd_count--;
	// 	exec = exec->next;
	// }
	// dup2(1, STDOUT_FILENO);
	// make_cmd(exec, data);
}

static t_exec	*create_cmd_arr(t_list *token, int len)
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

static void	exec_addback(t_exec **exec, t_exec *node)
{
	t_exec	*temp;

	temp = *exec;
	if (*exec == NULL)
		*exec = node;
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = node;
	}
}
