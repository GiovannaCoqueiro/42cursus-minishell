#include "minishell.h"

void	exit_builtin(t_data *data)
{
	t_exec *temp;
	int		num;

	temp = data->exec;
	num = 0;
	if (!data->exit_status)
		num = data->exit_status;
	if (temp->cmd[1])
		num = atoi(temp->cmd[1]);
	free_for_all(data);
	exit(num);
}

// exit tambem precisa lidar com argumentos
// exit sempre retorna um numero de 0 até a 255
// exit recebe numeros dentro do int max
// se ultrapassar o int max, retornamos 0

// caso o comando anterior deu errado, e a pessoa usou 'exit' sem numeros, nós retornamos 127
// caso o comando anterior deu certo, e a pessoa usou 'exit' sem numeros, nós retornamos 0