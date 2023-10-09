#include "minishell.h"

void	cd_builtin(t_data *data, char **args)
{
	int			len;
	struct stat	file_info;

	len = ft_arrsize(args);
	if (len > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		data->exit_status = 1;
		return ;
	}
	else if (len == 1)
		chdir(data->home);
	else if (len == 2)
	{
		if (stat(args[1], &file_info) == 0)
			chdir(args[1]);
	}
	data->exit_status = 0;
}
