#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <signal.h>

/* Error defines */
# define SUCCESS 0
# define FAILURE 1
# define ERRBUILTIN 2
# define ERRCMD_NOTEXEC 126
# define ERRCMD_NOTFOUNT 127
# define ERR_INVALIDARG 128
# define ERR_CTRLC 130

/* Token */
enum e_token
{
	INFILE = 1,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE,
	BULTIN,
	CMD,
	ARG
};

typedef struct s_var
{
	char	*str;
	char	*var;
	char	*value;
}	t_var;

typedef struct s_data
{
	char	*prompt;
	char	**path;
	t_list	*env;
	t_var	*var;
}			t_data;

/* Main */
void	read_prompt(t_data *data);
void	copy_env(t_list **list, char **env);
char	**save_path(char **envp);
void	init_readline(t_data *data);

/* Free */
void	free_for_all(t_data *data);
void	free_str_arrs(char **arr);
void	free_list(t_list *list);

/* Builtin */
void	exit_builtin(t_data *data);
void	env_builtin(t_data *data);
void	pwd_builtin(void);
void	unset_builtin(t_data *data);

/* Signal */
void	signal_handler(int signal);
void	signal_ignore(void);
void	signal_default(void);

#endif