#include "minishell.h"

void	env_builtin(t_data *data, char **args)
{
	t_list	*temp;

	if (ft_arrsize(args) > 1)
	{
		ft_putendl_fd("env: too many arguments", 2);
		data->exit_status = 127;
		return ;
	}
	temp = data->env;
	while (temp != NULL)
	{
		if (temp->content && ft_strchr((char *)temp->content, '=') != NULL)
			printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	data->exit_status = 0;
}
