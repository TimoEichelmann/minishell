/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:44 by snegi             #+#    #+#             */
/*   Updated: 2024/04/19 15:16:08 by teichelm         ###   ########.fr       */
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

typedef struct s_shell {
	char	*path;
	char	**command_path; //splitted
	char	**command_arg; //command arguments
	char	*command;
}	t_shell;

typedef	struct s_cmd {
	char	*cmd;
	char	*option;
	char	*arg;
	char	*input;
	char	*token;
}	t_cmd;

typedef struct s_env {
	char	*var;
}	t_env;


char *maintain_cd(char *input, char *promt) ;
void	ft_env(t_list *env);
void	del_env(t_list *env);
char	*ft_getenv(t_list *env, char *name);
t_list	*init_env(char **ev);
void	echo(char *input, t_list *env);
int	substr_len(char *substr);
void	free_cmd(t_cmd *cmd);
void	ft_exit(t_list *env);
char	*cmd_read(char *input, int *j);
int	is_token(char *c);
char	*arg_read(char *input, int *j);
char	*token_read(char *input, int *j);
t_cmd	*parser(char *input, t_list *env);
int	unclosed_quotes(char *input);
int	iterate_quotes(char *input, int ind, int i);
void	command_parser(char	*input, t_cmd **cmd, int cmd_count);
int	command_counter(char *input);
int	command_lexer(t_cmd *cmd, t_list *env);
int	own_lexer(t_cmd *c, int ind, t_list *env);
void	expander(t_cmd *cmd, t_list *env);
char	*exchange(char *arg, int index, t_list *env);
void	env_lexer(t_cmd cmd);
int	own_check(char *cmd);
char	*input_read(char *input, int *j);
char	*delete_quotation(char *input);
char	*opt_read(char *input, int *j);
#endif
