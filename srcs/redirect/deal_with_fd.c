#include "minishell.h"

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
