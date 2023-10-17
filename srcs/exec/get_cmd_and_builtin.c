#include "minishell.h"

static int		is_redirect(int lex);
static t_exec	*create_cmd_arr(int *lex, t_list *token, int len, int size);
static char		*copy_str(t_list *token);

void	get_cmd_and_args(t_list *token, int *lexer, t_data *data)
{
	t_list	*temp;
	int		len;
	int		redirect;

	len = 0;
	redirect = 0;
	temp = token;
	while (temp != NULL && lexer[len] != PIPE)
	{
		if (lexer[len] == CMD)
			data->has_cmd = 1;
		else if (lexer[len] == BUILTIN)
			data->has_builtin = 1;
		else if (is_redirect(lexer[len]) == 1)
		{
			temp = temp->next;
			len++;
			redirect += 2;
		}
		temp = temp->next;
		len++;
	}
	if (data->has_cmd == 1 || data->has_builtin == 1)
		data->exec = create_cmd_arr(lexer, token, len, len - redirect);
}

static int	is_redirect(int lex)
{
	if (lex == INFILE)
		return (1);
	else if (lex == OUTFILE)
		return (1);
	else if (lex == HEREDOC)
		return (1);
	else if (lex == APPEND)
		return (1);
	return (0);
}

static t_exec	*create_cmd_arr(int *lex, t_list *token, int len, int size)
{
	int		i;
	int		j;
	t_exec	*exec;

	exec = ft_calloc(sizeof(t_exec), 1);
	exec->lex = lex[0];
	exec->fd_in = -2;
	exec->fd_out = -2;
	exec->cmd = ft_calloc(sizeof(char *), size + 1);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (is_redirect(lex[i]) == 0)
			exec->cmd[j++] = copy_str(token);
		else
		{
			i++;
			token = token->next;
		}
		i++;
		token = token->next;
	}
	exec->cmd[j] = NULL;
	return (exec);
}

static char	*copy_str(t_list *token)
{
	char	*cmd;

	cmd = ft_calloc(sizeof(char), ft_strlen(token->content) + 1);
	ft_strlcpy(cmd, token->content, ft_strlen(token->content) + 1);
	return (cmd);
}
