/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboiarin <aboiarin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:15:43 by avoronko          #+#    #+#             */
/*   Updated: 2024/04/29 18:10:31 by aboiarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <setjmp.h>
# include <signal.h>
# include "src/libft/libft.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define SAVE_FD 0
# define RESTORE_FD 1
# define CLOSE_FD 2

# define MAX_ARGS 200

extern volatile int	g_signal_received;

typedef struct s_data
{
	char			*input;
	char			*prompt;
	struct s_cmd	*commands;
	struct s_token	*tokens;
	char			**env;
	int				stdin_save;
	int				stdout_save;
	int				exit_status;
}	t_data;

typedef struct s_cmd
{
	char			*args[MAX_ARGS + 1];
	char			**input;
	char			**output;
	int				output_counter;
	int				input_counter;
	int				append;
	bool			heredoc;
	char			*heredoc_delimiter;
	char			*h_input;
	bool			pipe;
	bool			is_first_token;
	struct s_cmd	*next;
}	t_cmd;

typedef enum e_token_type
{
	WORD,
	TOKEN_SPACE,
	TOKEN_TAB,
	TOKEN_NEWLINE,
	PIPE,
	ENV,
	REDIR_IN,
	REDIR_OUT,
	APPEND,
	HEREDOC,
	QUOTE,
	DOUBLEQUOTE,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*previous;
	struct s_token	*next;
}	t_token;

typedef struct s_ls
{
	t_token			*first;
	t_token			*current;
	t_data			*data;
}	t_ls;

typedef enum status
{
	success = 0,
	nferr = 1,
	ferr = -1,
	epipe = 2
}	t_exs;

typedef struct s_pipe
{
	int		pipefd[2];
	pid_t	*pids;
	pid_t	pid;
	int		in_fd;
	int		out_fd;
	int		i;
}	t_pipe;

/************************** MAIN ************************************/

//main
int		main_loop(t_data *data);
void	run_minishell(t_data *data);
void	exit_minishell(t_data *data, int exit_code);

//main_utils
char	*get_prompt(void);
int		handle_error(const char *subject, char *message, t_exs error_code);
int		init_data_env(t_data *data);
void	set_exit_status(t_data *data, int result, int flag);

//echoctl
void	enable_echoctl(void);
void	disable_echoctl(void);

//signals
void	signals_noninteractive(void);
void	signals_interactive(void);
void	display_new_line(int signum);
void	reset_line(int signum);

//free
void	free_arr(char **arr);
void	free_tokens(t_token *tokens);
void	free_command(t_cmd *command);
void	free_pipeline(t_cmd *command);
void	free_data(t_data *data, int flag);

/************************** LEXER ************************************/

//lexer
int		lexer(t_data *data);
int		lexer_loop(t_ls *ls);
int		process_words(t_ls *ls, int *i);
int		create_word_token(t_ls *ls, int start, int *i);
bool	is_not_word(char symbol);

//handle nonwords
bool	process_non_words(t_ls *ls, int *i);
int		process_env(t_ls *ls, int *i);
int		process_redirection(t_ls *ls, int *i);

// tokens_init
int		token_init(t_ls *ls, t_token_type type, const char *value);
t_ls	*init_lexer_state(t_data *data);

/**************************** PARSER ************************************/

//parser
int		parser(t_data *data);
int		parsing_loop(t_data *data, t_cmd **first_cmd, t_token **tokens,
			t_token **last_tkn);
int		single_cmd(t_data *data, t_cmd *cmd, t_token *tokens,
			t_token **last_token);
int		handle_token(t_data *data, t_cmd *command, t_token **current, int *ac);

//token checks
bool	check_tokens(t_cmd *command, t_token *tokens);
bool	is_valid_after_pipe(t_token **token, t_cmd *current_command);
bool	are_quotes_closed(t_token *tokens);
void	toggle_quote_states(t_token *tokens, bool *quote, bool *double_quote);

//check redirections
bool	validate_redirection_syntax(t_token *tokens, t_cmd *command);
bool	check_output_redir(t_token **current_token, t_cmd *command);
bool	check_input_redir(t_token **current_token, t_cmd *command);
bool	has_valid_filename_after_redirection(t_token *current_token);

//handle_redirect
int		handle_output_redirect(t_data *data, t_cmd *command, t_token **current);
int		handle_input_redirect(t_data *data, t_cmd *command, t_token **current);
char	*handle_heredoc(t_cmd *command, t_token **current_token);
int		get_ofilename(t_data *data, t_cmd **command, t_token **next);
int		get_ifilename(t_data *data, t_cmd **command, t_token **next);

//handle_quotes
void	handle_quotes(t_data *data, t_cmd *command, t_token **current, int *ac);
char	*handle_single_quote(t_token **token);
char	*handle_double_quote(t_data *data, t_token **token);
char	*add_quoted_string(t_token **token, char **quoted_string);

//handle_env
char	*handle_quoted_env(t_data *data, t_token *token, char **quoted_string);
void	handle_env(t_data *data, t_cmd *command, int *ac, t_token *token);
char	*expand_tilda(t_data *data, char *env_name);
char	*expand_env_variable(t_data *data, char *env_name);
char	*ft_getenv(t_data *data, const char *env_name);

//parser utils
void	decide_if_join(t_cmd *command, t_token *token, char *current, int *ac);
int		initialize_output_array(t_cmd *cmd);
int		initialize_input_array(t_cmd *cmd);
bool	is_redirect_type(t_token *temp_tokens);

//init_cmds
t_cmd	*initialize_parsing(void);
t_cmd	*initialize_command(void);
int		new_command(t_cmd **current_command);

//add_input
bool	process_h_input(t_cmd *cmd);
bool	handle_empty_pipe(t_data *data);
char	*append_input(char *original, const char *to_append);

/**************************** EXECUTOR ************************************/

//executor
int		executor(t_cmd *command, t_data *data);
int		execute_command(t_cmd *cmd, t_data *data);
int		execute_single_command(t_cmd *cmd, t_data *data);
int		execute_built_in(t_cmd *command, t_data *data);

//pipeline
int		execute_pipeline(t_cmd *cmd, t_data *data);
void	handle_child_process(t_pipe *pd, t_cmd *cmd, t_data *data);
void	handle_parent_process(t_cmd *cmd, t_pipe *pd);
int		finalize_pipeline(pid_t *pids, int count);
int		fork_and_execute(t_pipe	*pd, t_cmd *cmd, t_data *data);

//execve
int		try_external_cmd(t_data *data, char **paths, t_cmd *cmd);
char	*create_full_path(const char *directory, const char *filename);
int		execute_execve(t_data *data, t_cmd *cmd);
int		execute_path(t_data *data, t_cmd *cmd);

//ex_utils
bool	is_builtin_command(const char *cmd);
int		count_commands(t_cmd *command);
void	manage_std_save(t_data *data, int flag);
int		create_pipe(t_pipe	*pd);
int		init_pipeline(t_cmd *cmd, pid_t **pids);

//execute redirections
int		execute_redir(t_data *data, t_cmd *command, int *in_fd, int *out_fd);
int		execute_input(char **input_filename, int *in_fd);
int		execute_heredoc(const char *heredoc_content, int *in_fd);
int		execute_output(char **output_filename, int append, int *out_fd);
/************************** BUILT INS ************************************/

//builtins
int		ft_echo(t_cmd *cmd, t_data *data);
int		ft_cd(t_cmd *cmd, t_data *data);
int		ft_pwd(t_cmd *cmd);
int		ft_env_sys(t_cmd *cmd, int c, t_data *data);
int		ft_export(t_cmd *cmd, t_data *data);
int		ft_unset(t_cmd *cmd, t_data *data);
int		ft_env(t_cmd *cmd, t_data *data, int flag);
int		ft_exit(t_cmd *cmd, t_data *data);

//builtins utils
int		ft_arrlen(char **arr);
bool	is_n(const char *arg, int *status);
int		cderror(char *temp, int status);
int		enverror(int status, char *name, char *value);
char	**env_copy(char **environ, char **env);
int		env_check(char *to_find, char *str);
char	*env_upd(char *env, char *upd);
char	*ft_envdup(const char *s);
void	env_create(t_data *data, char *name, char *value);
int		pre_export(char *input, char **name, char **value);
int		echerror(int status);

#endif