/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:44 by snegi             #+#    #+#             */
/*   Updated: 2024/05/04 22:42:20 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include "./libft/libft.h"

typedef struct s_basic
{
	char	*input;
	int		pipe_num;
	int		exit_status;
	char	**env;
}	t_basic;

typedef struct s_shell {
	int		file;
	int		ofile;
	char	*path;
	char	**command_path;
	char	**command_arg;
	char	*command;
}	t_shell;

typedef struct s_cmd {
	char	*cmd;
	char	*input;
	char	*arg;
	int		token;
	int		ired;
	int		ored;
	char	*ifile;
	char	*ofile;
}	t_cmd;

typedef struct s_count {
	int	i;
	int	quote_count;
	int	count;
	int	count2;
	int	j;
}	t_count;

void	print_error(char *str);
void	ft_exit(char **env);
void	free_memory(t_shell *shell);
int		substr_len(char *substr);
int		unclosed_quotes(char *input);
int		iterate_quotes(char *input, int ind, int i);
void	del_env(char **env);
char	*ft_getenv(char **env, char *name);
char	**init_env(char **ev);
char	**copy_environment(char **old, int ind);
int		ft_env(char **env);
int		own_check(char *cmd);
int		our_functions(t_cmd *cmd, t_basic *basic);
void	single_exec(t_cmd *cmd, t_basic *basic);
int		main_exec(t_basic *basic, t_cmd *cmd );
char	*get_command(char **path, char *command);
int		maintain_cd(char *input, char **env);
void	free_cmd(t_cmd *cmd);
char	*cmd_read(char *input, int *j);
int		is_token(char *c);
char	*arg_read(char *input, int ind, int *j);
char	*token_read(char *input, int *j, char **file);
t_cmd	*parser(char *input, char **env, int ex);
char	*expander(char *str, char **env, int ex_status);
char	*exchange(char *arg, int index, char **env);
int		env_lexer(t_cmd cmd);
char	*input_read(char *input, int *j);
char	*delete_quotation(char *input);
int		echo(t_cmd *cmd);
int		ft_unset(char **env, char *name);
int		add_var(char ***ev, char *arg, int i);
int		ft_export(char ***ev, char *arg);
int		token_check(t_cmd *cmd, t_shell *shell);
int		check_path(char *str, t_shell *shell);
int		count_cmds(char *input);
int		check_quotation(char **splitted);
void	free_splitted(char **splitted);
int		check_empty(char **splitted);
int		check_redirections_loop(char *s, int c1, int c2, int quote_count);
int		before(char *str, int i);
char	*realloc_redirection(char *str, int i);
int		parse_redirections(char	**str, int i);
int		check_redirections(char **s);
int		print_check(int ind, char **splitted);
char	*word(char *p);
char	*cmd_word_check(char *p);
int		check_words(char **splitted);
int		checks(char **splitted);
int		own_check(char *cmd);
char	**lexer(char *input);
char	*cmd_read(char *input, int *j);
int		check_true_arg(char *input);
char	*arg_read(char *input, int ind, int *j);
int		redirection_need(char *input);
void	input_need(t_cmd *cmd, int need, char *input, int *j);
void	output_need(t_cmd *cmd, int need, char *input, int *j);
void	redirection_read(t_cmd *cmd, char *input, int *j);
char	*truncate_input(char *input);
int		cmd_parser(t_cmd *cmd, char *input, int pipe);
t_cmd	*cmd_creator(char **splitted);
char	*paste_var(int index, char *arg, char *var, char **env);
char	*exchange(char *arg, int index, char **env);
void	ft_paste(char *result, char *str, char *num);
char	*paste_ex_status(char *str, int ex_status);
char	*paste_tilde(int index, char *str, char *result, char **env);
char	*tilde_expansion(char *str, int index, char **env);
char	*expander(char *str, char **env, int ex_status);
char	*delete_quotation(char *input);
int		remove_quotation(t_cmd *cmd);
void	expansion(t_cmd *cmd, char **env, int ex);
t_cmd	*parser(char *input, char **env, int ex);
void	free_cmd(t_cmd *cmd);

#endif
