#include "minishell.h"

static int	verify_redirect(int lex, char *file, int *fd_in, int *fd_out);
static int	open_file(char *file, int mode, int *fd_in, int *fd_out);

int	validate_files(t_list *token, int *lexer, int *fd_in, int *fd_out)
{
	t_list		*temp;
	int			i;

	*fd_in = -2;
	*fd_out = -2;
	i = -1;
	temp = token;
	while (temp->next != NULL && lexer[++i] != PIPE)
	{
		if (verify_redirect(lexer[i], (char *)temp->next->content,
				fd_in, fd_out) == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

static int	verify_redirect(int lex, char *file, int *fd_in, int *fd_out)
{
	struct stat	file_info;

	if (lex == OUTFILE)
		*fd_out = open_file(file, OUTFILE, fd_in, fd_out);
	else if (lex == APPEND)
		*fd_out = open_file(file, APPEND, fd_in, fd_out);
	else if (lex == INFILE)
	{
		if (stat(file, &file_info) == 0)
			*fd_in = open_file(file, INFILE, fd_in, fd_out);
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
	return (1);
}

static int	open_file(char *file, int mode, int *fd_in, int *fd_out)
{
	int	fd;

	if (mode == INFILE)
	{
		if (*fd_in != -2)
			close (*fd_in);
		fd = open(file, O_RDONLY);
	}
	else if (mode == OUTFILE)
	{
		if (*fd_out != -2)
			close (*fd_out);
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0777);
	}
	else
	{
		if (*fd_out != -2)
			close (*fd_out);
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0777);
	}
	return (fd);
}

void	redirect_files(int fd_in, int fd_out)
{
	if (fd_in != -2)
		dup2(fd_in, 0);
	if (fd_out != -2)
		dup2(fd_out, 1);
}

void	close_files(int fd_in, int fd_out)
{
	if (fd_in != -2)
		close(fd_in);
	if (fd_out != -2)
		close(fd_out);
}
