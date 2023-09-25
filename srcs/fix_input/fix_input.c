#include "minishell.h"

void	check_var(t_list *token, t_list *env)
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
	while (temp != NULL)
	{
		str = ft_strdup((char *)temp->content);
		str = search_and_remove_quotes(str);
		free(temp->content);
		temp->content = ft_strdup(str);
		printf("content: %s\n", (char *)temp->content);
		free(str);
		temp = temp->next;
	}
}
