#include "minishell.h"

static int	open_file(char *file, int mode, int *fd_in, int *fd_out);

int	validate_files(t_list *token, int *lexer, int *fd_in, int *fd_out)
{
	struct stat	file_info;
	t_list		*temp;
	int			i;

	*fd_in = -2;
	*fd_out = -2;
	i = -1;
	temp = token;
	while (temp != NULL && lexer[++i] != PIPE)
	{
		if (lexer[i] == OUTFILE)
			*fd_out = open_file(temp->next->content, 2, fd_in, fd_out);
		else if (lexer[i] == APPEND)
			*fd_out = open_file(temp->next->content, 3, fd_in, fd_out);
		else if (lexer[i] == INFILE)
		{
			if (stat(temp->next->content, &file_info) == 0)
				*fd_in = open_file(temp->next->content, 1, fd_in, fd_out);
			else
			{
				if (*fd_in != -2)
					close (*fd_in);
				if (*fd_out != -2)
					close (*fd_out);
				ft_printf_fd(2, "No such file or directory\n");
				return (0);
			}
		}
		temp = temp->next;
	}
	return (1);
}

static int	open_file(char *file, int mode, int *fd_in, int *fd_out)
{
	int	fd;

	if (mode == 1)
	{
		if (*fd_in != -2)
			close (*fd_in);
		fd = open(file, O_RDONLY);
	}
	else if (mode == 2)
	{
		if (*fd_out != -2)
			close (*fd_out);
		fd = open(file, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	}
	else
	{
		if (*fd_out != -2)
			close (*fd_out);
		fd = open(file, O_APPEND | O_CREAT | O_WRONLY, 0777);
	}
	return (fd);
}
