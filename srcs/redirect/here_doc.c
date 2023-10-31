#include "minishell.h"

static int	open_heredoc(t_data *data, int size);
static int	open_file(char *file);
static void	write_on_heredoc(int fd, char *end_msg);
// static char	*get_line(int fd);

int	check_heredoc(t_data *data)
{
	int		i;
	int		size;
	t_list	*temp;

	i = -1;
	size = 0;
	temp = data->token;
	while (temp != NULL)
	{
		if (data->lexer[++i] == HEREDOC)
			size++;
		temp = temp->next;
	}
	if (size > 0)
		if (open_heredoc(data, size) == 0)
			return (0);
	return (1);
}

static int	open_heredoc(t_data *data, int size)
{
	t_list	*temp;
	int		i;
	int		index;

	data->fd_heredoc = ft_calloc(sizeof(int), size);
	temp = data->token;
	i = -1;
	index = 0;
	while (temp != NULL)
	{
		if (data->lexer[++i] == HEREDOC)
		{
			data->fd_heredoc[index] = open_file((char *)temp->next->content);
			write_on_heredoc(data->fd_heredoc[index],
				(char *)temp->next->content);
			close(data->fd_heredoc[index++]);
		}
		temp = temp->next;
	}
	return (1);
}

static int	open_file(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT, 0644);
	return (fd);
}

static void	write_on_heredoc(int fd, char *end_msg)
{
	char	*temp;

	while (true)
	{
		signal(SIGINT, sigint_parent_process);
		signal(SIGQUIT, SIG_IGN);
		temp = readline("> ");
		if (temp == NULL)
		{
			ft_putchar_fd('\n', 1);
			break ;
		}
		if (ft_strncmp(temp, end_msg, ft_strlen(end_msg)) == 0)
		{
			ft_putstr_fd("\n", fd);
			free(temp);
			break ;
		}
		ft_putstr_fd(temp, fd);
		ft_putstr_fd("\n", fd);
		free(temp);
	}
}
