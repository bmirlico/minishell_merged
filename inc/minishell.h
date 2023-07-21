/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmirlico <bmirlico@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 14:24:06 by bmirlico          #+#    #+#             */
/*   Updated: 2023/07/21 20:40:38 by bmirlico         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line_bonus.h"
# include "../libft/inc/ft_printf.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

# define DELIMITER " "
# define SPECIAL_CHAR "#&~*`();\\"
# define SINGLE_OPEN 1
# define DOUBLE_OPEN 2
# define CLOSED 3

// tokens de l'input
typedef enum s_token_type {
	T_SPACE,
	T_CMD,
	T_PIPE,
	T_LR,
	T_RR,
	T_HEREDOC,
	T_APPEND,
	T_INFILE,
	T_LIMITOR,
	T_OUTFILE,
	T_OUTFILE_APPEND,
	T_SINGLEQ,
	T_DOUBLEQ,
	T_EOF,
}	t_token_type;

// utilisee pour dupliquer l'env (tableau de tableaux) en list
typedef struct s_env {
	char			*var_name;
	char			*var_value;
	struct s_env	*next;
}	t_env;

// utilisee pour creer la liste caractere par caractere et la la liste de str
typedef struct s_token {
	t_token_type	type;
	char			value;
	char			*str;
	int				fd;
	struct s_token	*next;
}	t_token;

// utilisee pour le parsing de commandes
typedef struct s_command {
	char					**cmd_args;
	t_token					*redirections;
	int						index;
	struct s_command		*next;
}	t_command;

// utilisee pour regrouper les element de la partie exec a free
typedef struct s_pipex {
	char					*path;
	char					**paths;
	int						nb_pipes;
	int						nb_cmds;
	pid_t					**pipefd;
	pid_t					*tab_pid;
	t_env					*copy_t_env;
	char					**copy_env_tmp;
	t_token					**copy_lst;
	t_token					**copy_lst_j;
	t_command				**copy_cmds;
}	t_pipex;

/* 0) MAIN */

// main.c @Bastien

void			minishell(t_env *env, char *input);

void			display_parser(t_command **lst);

void			display_lexer(t_token **lst);

void			display_lexers(t_token **lst, t_token **lst_j);

/* 0-bis) PRE-PARSING i.e gestion d'erreurs et caracteres speciaux */

// syntax_error_1.c @Clement

int				check_syntax(char *input);

int				check_pipe_error(char *input);

int				check_empty_and_double_pipe(char *input);

int				check_redirections(char *input);

int				check_empty_redirection(char *input);

// syntax_error_2.c @Clement

int				check_special_char(char *input);

int				check_bad_env_variable(char *input);

int				check_last_exitcode_case(char *input, int index);

int				check_rdir(int rdir);

// utils.c @Bastien @Clement

int				is_special_char(char c);

int				quotes_state(char c, int prev_state);

int				is_delimiter(char c, char *delimiter);

void			ft_strncpy(char *value, char *input, int len);

int				count_slash(char *str);

/* 1) LEXER i.e tokenisation de l'input */

// lexer_1.c @Bastien

void			lexer_str(t_token **lst, t_token **lst_j);

void			group_quotes(t_token **tmp, char **join);

void			group_str(t_token **tmp, t_token **lst_j, char *join);

void			group_redirs(t_token **tmp, t_token **lst_j, char *join);

void			add_char_to_str(t_token **tmp, t_token **lst_j, char *join);

// lexer_2.c @Bastien

void			tokenize_remaining(t_token **lst_j);

void			ft_join_free(char **join, char c);

char			*char_to_str(char c);

void			lexer_char(t_token **lst, char *input);

char			get_token_value(char *input);

// lexer_3.c @Bastien

t_token_type	get_token_type(char c);

// lexer_list.c @Bastien

t_token			*create_list_lexer(void);

t_token			*create_token(t_token_type type, char c, char *str);

void			push_to_list(t_token **lst, t_token *new);

void			free_lexer_char(t_token **lst);

void			free_lexer_str(t_token **lst);

/* 2) PARSING i.e traitement syntaxique de l'input */

// parser_1.c @Bastien

void			parser(t_token **lst_j, t_command **cmds);

void			add_redirs(t_token **tmp, t_token **redirs);

void			add_command_to_tab(t_token **tmp, char ***tab);

void			add_command_to_list(t_token **tmp, t_token **redirs,
					char ***tab, t_command **cmds);

void			fill_tab_free(char ***tab, char *str);

// parser_2.c @Bastien

void			fill_in_tmp(char **dest, char **src, int len);

void			free_previous_str(char **tab, int i);

int				get_len_tab(char **tab);

void			free_tab(char **tab);

// parser_list.c @Bastien

t_command		*create_list_parser(void);

t_command		*create_command(char **tab, t_token *redirs);

void			push_to_parser(t_command **lst, t_command *new);

void			free_parser(t_command **cmds);

void			free_lists(t_token **lst, t_token **lst_j, t_command **cmds);

/* 3) EXPAND i.e traitement des variables d'env */

// var_env_state.c @Clement

int				var_env_state(char *str, int i, int var_env_state, int q_state);

int				var_env_declaration(char *str, int i, int quote_state);

int				end_var_env_declaration(char *str, int i);

int				is_closing_scope(char *str, int index);

// expand_substitution.c @Clement

int				to_be_modified(char *str);

int				nb_quotes(char *str);

void			new_str(t_env *env, char *str, char *new);

int				var_env_copy(t_env *env, char *str, char *new, int dest);

char			*get_env(t_env *env, char *name);

// get_expand_info @Clement

int				get_varname_len(char *str);

int				get_varenv_value_len(t_env *env, char *str);

int				get_varenv_len(t_env *env, char *str, int i);

int				get_var_env_end(char *str, int i);

int				get_nb_empty(char **tab);

// clean_post_expand.c @Clement

void			clean_lst(t_command *cmds);

char			**replace_tab(char **tab, int new_len);

// expand.c @Clement

void			expand(t_env *env, t_command **cmds);

void			expand_tab(t_env *env, char **tab);

void			expand_str_tab(t_env *env, char **tab, int i);

void			expand_rdir(t_env *env, t_token	*redirections);

void			expand_rdir_lst(t_env *env, t_token *rdir);

// remove_quote.c @Clement

void			remove_quotes_rdir(t_token	*redirections);

void			quote_removing_rdir(t_token *rdir, int quotes);

void			remove_quotes_tab(char **tab);

void			quote_removing_tab(char **tab, int index, int quotes);

/* 4) EXECUTION i.e execution des commandes */

// 4.1. Dupliquer l'environnement

// dup_env.c @Clement

void			dup_env(char **envp, t_env **env);

void			fill_t_env(t_env *new, char *str);

void			display_env(t_env *env);

char			**create_env_tab(t_env *env);

void			display_tab(char **tab);

// lst_env_utils.c @Clement

int				lst_env_size(t_env *env);

void			free_envlst(t_env **env);

void			add_back_to_env(t_env **env, t_env *new);

void			new_return_value(t_env *env, char *return_value);

// 4.2. Execution

// exec_1.c @Bastien

// void			execution(char *input, t_command **cmds, char **env,
// 					t_pipex vars);
void			execution(t_pipex vars);

void			pipex(t_command *tmp, t_pipex vars, t_token **rdirs);

void			child_process(t_command *tmp, t_pipex vars, t_token **rdirs);

void			wait_exit_code(t_pipex vars);

void			exec_cmd(t_command *tmp, t_pipex vars);

// exec_2.c @Bastien

void			handle_exec(char *cmd_p, t_command *tmp, t_pipex vars);

void			if_file_unexists(char *cmd_p, t_command *tmp, t_pipex vars);

void			if_file_exists(char *cmd_p, t_command *tmp, t_pipex vars);

// pipe_.c @Bastien

pid_t			**init_pipefd(int nb_pipes);

void			init_pipe(t_pipex vars, int j);

void			close_previous_pipe(t_pipex vars, int j);

void			close_pipe(t_pipex vars, int j);

void			free_pipefd(pid_t **pipefd, int nb_pipes);

// pipe_rdirs_1.c @Bastien

void			pipe_redirection(t_pipex vars, t_token **rdirs, int i);

void			pipe_first(t_pipex vars, int i, t_token **rdirs);

void			pipe_last(t_pipex vars, int i, t_token **rdirs);

void			pipe_between(t_pipex vars, int i, t_token **rdirs);

void			pipe_between_infile(t_token *last_infile, t_pipex vars,
					int i);

// pipe_rdirs_2.c @Bastien

void			pipe_between_outfile(t_token *last_outfile, t_pipex vars,
					int i);

void			init_last_rdirs(t_token **last_infile, t_token **last_outfile,
					t_token **rdirs);

t_token			*get_last_infile(t_token **rdirs);

t_token			*get_last_outfile(t_token **rdirs);

// rdirs_.c @Bastien

void			open_rdirs(t_token **redirections);

void			handle_errors_rdirs(t_command *tmpc, t_pipex vars,
					t_token **rdirs);

void			close_pipe_and_free(t_pipex vars, int index);

void			close_rdirs(t_token **redirections);

void			fill_heredoc(t_token *tmp);

// utils_exec_1.c @Bastien

void			init_struct(t_pipex *vars);

void			get_index_cmds(t_command **cmds);

// int				get_nb_pipes(char *input);
int				lst_cmd_size(t_command *lst);

int				count_slash(char *str);

char			*ft_strjoin3(char *str1, char *str2, char *str3);

// utils_exec_2.c @Bastien

char			*get_path(char **env);

int				is_path_set(char **env);

char			*get_cmd_with_path(char *cmd, char **paths);

void			copy_lists(t_pipex *vars, t_token **lst, t_token **lst_j,
					t_command **cmds);

void			free_and_exit(t_pipex vars);

// utils_exec_3.c @Bastien

void			free_pipex(t_pipex vars);

void			free_vars(t_pipex vars);

/* 5) BUILT-INS et des builtins */
// echo, cd, pwd, export, unset, env, exit

// builtin.c @Bastien

int				is_builtin(char *cmd);

void			exec_builtin(t_command *tmp, t_pipex vars);

void			builtin_redirection(int *old_stdout, t_command *tmp,
					t_pipex vars);

int				errors_rdirs_builtin_alone(t_command *tmp, t_pipex vars);

void			builtins(int len, t_command *tmp, t_pipex vars);

// cd.c @Bastien

void			built_in_cd(t_command *tmp);

// pwd.c @Bastien

void			built_in_pwd(void);

// exit_1.c @Bastien

void			built_in_exit(t_command *tmp);

void			conditions_exit(t_command *tmp, long long exit_code,
					char *error_str, int len_tab);

int				is_numeric(char *str);

void			exit_non_numeric(char **error, char *str);

int				is_out_of_range(long long exit_code, char *str);

// exit_2.c @Bastien

long long		ft_strtoll(const char *nptr);

void			init_strtoll(int *i, int *sign, long long *res, int *digit);

void			check_sign(char c, int *i, int *sign);

void			handle_bounds(int *sign, long long *res);

// env.c @Clement

void			built_in_env(t_command *tmp, t_pipex vars);

// unset.c @Clement

void			built_in_unset(t_command *cmd, t_env *env);

void			unset(t_env *env, char *name);

void			delete_first(t_env *env);

// export.c @Clement

void			built_in_export(t_command *cmd, t_env *env);

int				affectation_is_complete(char *str);

void			export(t_env *env, char *declaration);

int				check_valid_identifier(t_env *env, char *str);

void			swap_value(t_env *env, char *declaration);

// export_display.c @Clement

void			display_export(t_env *env);

void			display_not_a_valid_identifier(char *str, t_env *env);

int				already_exist(t_env *env, char *declaration);

// echo.c @Clement

void			built_in_echo(t_command *cmd, t_env *env);

void			echo(t_command *cmd, t_env *env);

int				no_expand_needed(char *str, t_env *env);

int				is_option_n(char *str);

// echo_special_case.c @Clement

void			print_echo(t_env *env, char *str);

int				print_echo_special(t_env *env, char *str);

void			print_varenv_no_space(char *str);

int				check_var_env(char *var);

int				is_special_var_env(char *str, int i, t_env *env);

#endif
