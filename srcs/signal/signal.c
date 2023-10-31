#include "minishell.h"

void	sigint_parent_process(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_ignore(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sigint_heredoc(int signal)
{
	if (signal == SIGINT)
		*get_heredoc_flag() = 1;
	close(STDIN_FILENO);
}
