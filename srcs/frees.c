#include "minishell.h"

void	free_for_all(t_data	*data)
{
	rl_clear_history();
	if (data->env != NULL)
		free_list(data->env);
	if (data->prompt != NULL)
		free(data->prompt);
	if (data->token != NULL)
		free_list(data->token);
	if (data->lexer != NULL)
		free(data->lexer);
	if (data->home != NULL)
		free(data->home);
	free(data);
}

void	free_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp != NULL)
	{
		list = list->next;
		if (temp->content)
			free(temp->content);
		free(temp);
		temp = list;
	}
}
