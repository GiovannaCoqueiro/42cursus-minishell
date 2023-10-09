#include "minishell.h"

void	env_builtin(t_data *data, char **args)
{
	t_list	*temp;

	if (ft_arrsize(args) > 1)
		return ;
	temp = data->env;
	while (temp != NULL)
	{
		if (temp->content && ft_strchr((char *)temp->content, '=') != NULL)
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
}

t_list	*copy_env_list(t_list *env, t_list *lst)
{
	while (env != NULL)
	{
		ft_lstadd_back(&lst, ft_lstnew(ft_strdup(env->content)));
		env = env->next;
	}
	return (lst);
}
