#include "minishell.h"

void	error_check(t_exec *exec)
{
	if (exec != NULL)
	{
		if (exec->all_paths != NULL)
			ft_free_str_arr(exec->all_paths);
		if (exec->cmd != NULL)
			ft_free_str_arr(exec->cmd);
	}
	perror("Error");
}
