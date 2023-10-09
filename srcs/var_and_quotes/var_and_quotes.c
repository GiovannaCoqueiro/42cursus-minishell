#include "minishell.h"

void	check_var(t_list *token, t_list *env, t_data *data)
{
	t_list	*temp;
	char	*str;

	temp = token;
	while (temp != NULL)
	{
		str = ft_strdup((char *)temp->content);
		str = search_and_expand_var(str, env);
		free(temp->content);
		temp->content = ft_strdup(str);
		free(str);
		temp = temp->next;
	}
	temp = token;
	check_tildes(temp, data->home);
	temp = token;
	while (temp != NULL)
	{
		str = ft_strdup((char *)temp->content);
		str = search_and_remove_quotes(str);
		free(temp->content);
		temp->content = ft_strdup(str);
		free(str);
		temp = temp->next;
	}
}
