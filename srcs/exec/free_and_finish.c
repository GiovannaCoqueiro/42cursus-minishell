#include "minishell.h"

void	error_check(t_exec *exec, t_data *data)
{
	if (exec != NULL)
	{
		if (data->all_paths != NULL)
			ft_free_str_arr(data->all_paths);
		if (exec->cmd != NULL)
			ft_free_str_arr(exec->cmd);
	}
	perror("Error");
}
