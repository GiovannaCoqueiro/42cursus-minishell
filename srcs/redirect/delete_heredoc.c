#include "minishell.h"

void	delete_heredoc_files(t_data *data)
{
	t_list	*temp;
	int		i;

	temp = data->token;
	i = -1;
	while (temp != NULL)
	{
		if (data->lexer[++i] == HEREDOC)
			unlink((char *)temp->next->content);
		temp = temp->next;
	}
}
