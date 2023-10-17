#include "minishell.h"

void	exit_builtin(t_data *data, pid_t *pids, char **args)
{
	long	num;

	num = 0;
	if (data->exit_status != 0)
		num = data->exit_status;
	if (ft_arrsize(args) > 2)
	{
		printf("exit: too many arguments\n");
		data->exit_status = 1;
		return ;
	}
	if (ft_arrsize(args) == 2)
		if (args[1])
			num = ft_atol(args[1]);
	free_builtin(data, pids);
	exit(num);
}
