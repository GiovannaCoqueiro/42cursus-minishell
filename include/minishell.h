#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>

/* Characteres */
# define METACHAR "<>| "
# define VAR_STOPER " \'\"/$"
# define BLANK "\t\n\v\f\r "
# define S_QUOTE '\''
# define D_QUOTES '\"'

/* Error defines */
# define SUCCESS 0
# define FAILURE 1
# define ERRBUILTIN 2
# define ERRCMD_NOTEXEC 126
# define ERRCMD_NOTFOUNT 127
# define ERR_INVALIDARG 128
# define ERR_CTRLC 130

/* Lexer */
enum	e_lexeme
{
	INFILE = 1,
	OUTFILE,
	HEREDOC,
	APPEND,
	PIPE,
	BUILTIN,
	CMD,
	ARG
};

typedef struct s_exec
{
	char			**cmd;
	int				cmd_count;
	struct s_exec	*next;
}			t_exec;

typedef struct t_args
{
	int		i;
	int		cmd_count;
	int		last_pi;
	int		pipis[2];
	int		pipes[2];
	char	**path;
	char	**env;
	t_exec	*exec;
}			t_args;

typedef struct s_data
{
	char	*prompt;
	char	*home;
	t_list	*env;
	t_list	*token;
	int		*lexer;
	t_exec	*exec;
	t_args	*args;
	int		exit_status;

}			t_data;

/* Init */
void	copy_env(t_list **list, char **env, t_data *data);
void	init_readline(t_data *data);
void	read_prompt(t_list *token, int *lexer, t_data *data);

/* Free */
void	free_for_all(t_data *data);
void	free_list(t_list *list);
void	free_exec(t_exec *exec);
void	free_args(t_args *args);

/* Builtin */
void	exit_builtin(t_data *data);
void	env_builtin(t_data *data);
void	pwd_builtin(void);
void	unset_builtin(t_data *data);
void	export_builtin(t_data *data);

/* Builtin Utils */
t_list	*copy_env_list(t_list *env, t_list *lst);

/* Signal */
void	signal_handler(int signal);
void	signal_ignore(void);
void	signal_default(void);

/* Token and syntax*/
int		tokenization(t_data *data);
int		lex_analysis(t_data *data);
int		syntax_analysis(int *lexer, int len);
int		is_quoted(char c, int identifier);

/* Fix input */
int		check_for_quotes(t_list *token);
void	check_var(t_list *token, t_list *env, t_data *data);
char	*search_and_expand_var(char *str, t_list *env);
void	check_tildes(t_list *token, char *home);
char	*search_and_remove_quotes(char *str);

/* Exec */
void	prepare_exec(t_data *data);
void	open_pipe(int *fd, t_exec *exec, t_data *data, int cmd_count);
void	pipe_it(t_exec *exec);
void	make_cmd(t_args *args);
void	cmd_search(t_args *args);
void	here_doc(char *end_msg, t_exec *exec);

/* Pipex */
void	execute(t_data *data, t_exec *exec);
char	**find_path(char **env);
void	try_paths(t_args *t_args);
void	free_str_arrs(char **arr);
void	commands_fork(t_args *args, t_data *data);
void	first_command(t_args *args);
void	middle_command(t_args *args);
void	last_command(t_args *args);
void	close_pipes(t_args *args);
void	recycle_pipe(t_args *args);

#endif