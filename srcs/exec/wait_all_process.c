#include "minishell.h"

void	wait_all_processes(t_data *data, pid_t *pids, int flag)
{
	int	i;

	i = -1;
	if (flag == 1)
	{
		waitpid(pids[++i], &data->exit_status, 0);
		if (WEXITSTATUS(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
	else
	{
		while (++i < data->process_count)
			waitpid(pids[i], &data->exit_status, 0);
		if (WEXITSTATUS(data->exit_status))
			data->exit_status = WEXITSTATUS(data->exit_status);
	}
}
