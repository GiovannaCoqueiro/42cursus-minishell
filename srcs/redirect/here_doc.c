#include "minishell.h"

// static void	here_doc_utils(int *fd, char *end_msg, t_exec *exec);
// static char	*get_line(int fd);

// int	check_heredoc(t_data *data)
// {
// 	t_list	*temp;
// 	int		i;

// 	temp = data->token;
// 	while (temp != NULL)
// 	{
		
// 	}
// }

// void	here_doc(char *end_msg, t_exec *exec)
// {
//     while (true)
// 	{
// 		data->token = NULL;
// 		data->lexer = NULL;
// 		data->prompt = readline("\033[1;35mgibi>\033[0m ");
// 		if (data->prompt == NULL)
// 		{
// 			ft_putendl_fd("exit", 1);
// 			break ;
// 		}
// 		if (ft_strlen(data->prompt) >= 1)
// 		{
// 			add_history(data->prompt);
// 			if (tokenization(data) == 1 && check_for_quotes(data) == 1)
// 			{
// 				check_var(data);
// 				read_prompt(data->token, data->lexer, data);
// 			}
// 			if (data->lexer != NULL)
// 				free(data->lexer);
// 			if (data->token != NULL)
// 				free_list(data->token);
// 		}
// 		free(data->prompt);
// 	}
// }

// static void	here_doc_utils(int *fd, char *end_msg, t_exec *exec)
// {
// 	dup2(, STDOUT_FILENO);
// 	while (true)
// 	{
// 		 = readline("\033[1;35mgibi>\033[0m ");
// 		if (data->prompt == NULL)
// 		{
// 			ft_putendl_fd("exit", 1);
// 			break ;
// 		}
// 		if (ft_strlen(data->prompt) >= 1)
// 		{
// 			add_history(data->prompt);
// 			if (tokenization(data) == 1 && check_for_quotes(data) == 1)
// 			{
// 				check_var(data);
// 				read_prompt(data->token, data->lexer, data);
// 			}
// 			if (data->lexer != NULL)
// 				free(data->lexer);
// 			if (data->token != NULL)
// 				free_list(data->token);
// 		}
// 		free(data->prompt);
// 	}
// 	dup2(STDOUT_FILENO, STDERR_FILENO);


// 	char	*temp;

// 	while (1)
// 	{
// 		temp = readline("> ");
// 		if (temp == NULL)
// 		{
// 			ft_printf_fd(2, "warning: here-document delimited
// 			by end-of-file (wanted '%s')", end_msg);
// 			break ;
// 		}
// 		if (ft_strlen(temp) >= 1)
// 		{
// 			add_history(temp);
// 			if (ft_strcmp(temp, end_msg) == 0)
// 			{
// 				free(temp);
// 				close(exec->outfile);
// 				break ;
// 			}
// 			ft_putstr_fd(temp, fd[1]);
// 		}
// 		free(temp);
// 	}
// }

// static char	*get_line(int fd)
// {
// 	char	*temp;
// 	char	*str;
// 	int		bytes_read;

// 	temp = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (temp == NULL)
// 		return (NULL);
// 	str = "\0";
// 	bytes_read = 1;
// 	while (ft_strchr(str, '\n') == NULL && bytes_read != 0)
// 	{
// 		bytes_read = read(fd, temp, BUFFER_SIZE);
// 		if (bytes_read < 0)
// 		{
// 			free (temp);
// 			return (NULL);
// 		}
// 		temp[bytes_read] = '\0';
// 		str = ft_strjoin(str, temp);
// 	}
// 	free(temp);
// 	return (str);
// }
