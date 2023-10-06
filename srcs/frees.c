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
	free_exec(data->exec);
	free_args(data->args);
	free(data);
}

void	free_args(t_args *args)
{
	if (args != NULL)
	{
		if (args->path != NULL)
			ft_free_str_arr(&args->path);
		if (args->env != NULL)
			ft_free_str_arr(&args->env);
	}
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

void	free_exec(t_exec *exec)
{
	t_exec	*temp;

	temp = exec;
	while (temp != NULL)
	{
		exec = exec->next;
		if (temp->cmd)
			ft_free_str_arr(&temp->cmd);
		free(temp);
		temp = exec;
	}
}
