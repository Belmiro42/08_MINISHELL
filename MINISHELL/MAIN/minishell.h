/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: razamora <razamora@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 01:49:54 by bmatos-d          #+#    #+#             */
/*   Updated: 2024/09/05 22:48:26 by razamora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define _GNU_SOURCE

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │									INCLUDES							│
//  └───────────────────────────────────────────────────────────────────────┘

# include "../LIBFT/libft.h"
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │									MACROS								│
//  └───────────────────────────────────────────────────────────────────────┘

# define DEL 1
# define KEEP 0
# define GREEN "\001\x1B[32m\002"
# define WHITE "\001\x1B[37m\002"

extern int				g_signal_triggered;

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │							STRUCTURE PROTOTYPING						│
//  └───────────────────────────────────────────────────────────────────────┘

typedef struct s_env	t_env;
typedef struct s_set	t_set;
typedef struct s_pipe	t_pipe;
typedef struct s_token	t_token;
typedef struct s_input	t_input;
typedef struct s_output	t_output;

//  ┌───────────────────────────────────────────────────────────────────────┐
//  │									SRUCTURES							│
//  └───────────────────────────────────────────────────────────────────────┘

// STRUCT DESCRIPTION: t_env
typedef struct s_env
{
	char				*key;
	char				*value;
	t_env				*next;
}						t_env;

// STRUCT DESCRIPTION: t_set
typedef struct s_set
{
	int					exit_val;
	char				*raw_text;
	t_pipe				*pipe;
	t_set				*next;
}						t_set;

// STRUCT DESCRIPTION: t_pipe
typedef struct s_pipe
{
	char				*raw_text;
	char				**args;
	t_pipe				*next;
	t_input				*in;
	t_output			*out;
	t_token				*token;
}						t_pipe;

// STRUCT DESCRIPTION: t_output
typedef struct s_output
{
	bool				append;
	char				*filename;
	t_output			*next;
	t_token				*token;
}						t_output;

// STRUCT DESCRIPTION: t_input
typedef struct s_input
{
	bool				heredoc;
	bool				expand;
	char				*filename;
	char				*tmp;
	t_input				*next;
	t_token				*token;
}						t_input;

// STRUCT DESCRIPTION: t_token
typedef struct s_token
{
	char				*token;
	t_token				*next;
	t_token				*quoted_expanded;
	t_token				*real_tokens;
	int					inquote;
}						t_token;

//  ┌───────────────────────────────────────────────────────────────────────┐
//  ├─────────────────────────STRING FUNCTIONS──────────────────────────────┤
//  └───────────────────────────────────────────────────────────────────────┘

//  ────────────────────────────────UTILS──────────────────────────────────

char					*ft_strjoin_mi(char *s1, char *s2, bool KD1, bool KD2);
int						ft_isspace(char c);
int						ft_arrlen(char **arr);
void					ft_freedbl(char **twodimmalloc);
char					*add_character(char s1, char *s2, bool free1);

//  ┌───────────────────────────────────────────────────────────────────────┐
//  ├─────────────────────────PARSING FUNCTIONS─────────────────────────────┤
//  └───────────────────────────────────────────────────────────────────────┘

t_set					*find_sets(char *str);
void					find_pipes(t_set *set);
void					tokenise(t_pipe *current, char *str);
int						quote_split_var_expansion(t_pipe *pipe, t_env *env);
int						word_splitting(t_pipe *pipe);
int						fix_empty(t_pipe *pipe);
void					heredoc_expander(t_pipe *pipe);
char					*variable_expansion(char *input, t_env *env);
t_set					*construct_parser_struct(char *input, t_env *env);

//  ────────────────────────────────UTILS──────────────────────────────────

int						parse_error(char *str, t_env *env);
bool					is_valid_arg(char *token, char *str, int iterator);
void					make_input_node(t_pipe *cur, bool param, char **fname);
void					make_output_node(t_pipe *cur, bool param, char **fname);
int						in_quotes(char c, int *quote);
void					ambiguous_redirect(t_input *file, t_output *output);
bool					no_errors(t_set *set);

//  ┌───────────────────────────────────────────────────────────────────────┐
//  ├───────────────────────ENVIRONMENT FUNCTIONS───────────────────────────┤
//  └───────────────────────────────────────────────────────────────────────┘

t_env					*create_env_variables(char **envp, int argc,
							char **argv);

//  ────────────────────────────────UTILS──────────────────────────────────

void					new_val_env(char *key, char *new_val,
							t_env **environment);
char					*get_val_env(char *key, t_env *environment);
void					del_var_env(char *key, t_env **environment);
char					**env_to_char(t_env *env);

//  ┌───────────────────────────────────────────────────────────────────────┐
//  ├─────────────────────────────BUILTINS──────────────────────────────────┤
//  └───────────────────────────────────────────────────────────────────────┘

int						env_builtin(char **arg, t_env *environment);
int						export_builtin(char **arg, t_env *environment);
int						echo_builtin(char **arg, t_env *environment);
int						pwd_builtin(char **arg, t_env *environment);
int						exit_builtin(char **arg, t_env *environment, t_set *s);
int						unset_builtin(char **arg, t_env *environment);
int						cd_builtin(char **arg, t_env *environment);
int						exec_builtin(char **args, t_env *env, char **envp,
							t_set *set);

//  ────────────────────────────────UTILS──────────────────────────────────

bool					builtin(char *str);

//  ┌───────────────────────────────────────────────────────────────────────┐
//  ├──────────────────────────────SIGNALS──────────────────────────────────┤
//  └───────────────────────────────────────────────────────────────────────┘

void					default_signals(void);
void					infunc_signals(void);
void					bash(void);
void					shellception(void);

//  ┌───────────────────────────────────────────────────────────────────────┐
//  ├────────────────────────────LIBERATION─────────────────────────────────┤
//  └───────────────────────────────────────────────────────────────────────┘

void					free_env(t_env *env);
void					free_parser_struct(t_set *set);
void					free_struct_main(t_set *set, t_env *env);
void					free_token(t_token *token);
//  ┌───────────────────────────────────────────────────────────────────────┐
//  ├──────────────────────────────ALLOCS───────────────────────────────────┤
//  └───────────────────────────────────────────────────────────────────────┘
t_pipe					*new_pipe(void);
t_set					*new_set(void);
t_token					*new_token(void);
t_input					*new_input(void);
t_output				*new_output(void);

//  ┌───────────────────────────────────────────────────────────────────────┐
//  ├──────────────────────────EXECUTION UTILS──────────────────────────────┤
//  └───────────────────────────────────────────────────────────────────────┘

// Cambiar mas tarde
int						one_exec(t_set *set, t_env *env);
int						multi_exec(t_set *set, t_env *env);
void					execute_command(char **s_cmd, char **envp);
int						catch_exit_code(int argc, pid_t *pids);
int						handle_infile(t_input *file);
int						handle_outfile(t_output *file);
void					handle_heredoc(t_pipe *pipe, t_env *env, t_set *set);

//  ────────────────────────────────UTILS──────────────────────────────────

void					msm_heredoc(char *limiter, int line);
char					*ft_find_path(char **envp);
int						open_file(char *file, int type);
int						ft_command_error(char *cmd, char **envp);
void					ft_error_file(int *file_pipe, char *file);
char					*ft_get_path(char **full_cmd, char **envp);
int						ft_strcmp(char *s1, char *s2);
int						finaly_openfile(char **av, int argc);
void					ft_close_fd_final(int fd, int *file_pipe);
char					*variable_expansion_hd(char *input, t_env *environment);
int						pipe_num(t_pipe *pipe);
void					is_shellception(char **args);
void					close_last_middle_fd(int *file_pipe, int *middle_file);
int						close_middle_fd(int *file_pipe, int *middle_file);
void					print_shekk(void);
void					set_exit_val(int exit_val, t_env *environment);
void					signals_exit_codes(t_env *environment);

#endif
