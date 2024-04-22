/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:44 by snegi             #+#    #+#             */
/*   Updated: 2024/04/22 17:40:38 by teichelm         ###   ########.fr       */
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
	char	*redirection;
	char	*token;
}	t_cmd;


char *maintain_cd(char *input, char *promt) ;
int	ft_env(char **env);
void	del_env(char **env);
char	*ft_getenv(char **env, char *name);
char	**init_env(char **ev);
void	echo(char *input, char **env);
int	substr_len(char *substr);
void	free_cmd(t_cmd *cmd);
void	ft_exit(char **env);
char	*cmd_read(char *input, int *j);
int	is_token(char *c);
char	*arg_read(char *input, int *j);
char	*token_read(char *input, int *j);
t_cmd	*parser(char *input, char **env);
int	unclosed_quotes(char *input);
int	iterate_quotes(char *input, int ind, int i);
char	**copy_environment(char **old, int ind);
void	command_parser(char	*input, t_cmd **cmd, int cmd_count);
int	command_counter(char *input);
int	command_lexer(t_cmd *cmd, char **env);
int	own_lexer(t_cmd *c, int ind, char **env);
void	expander(t_cmd *cmd, char **env);
char	*exchange(char *arg, int index, char **env);
void	env_lexer(t_cmd cmd);
int	own_check(char *cmd);
char	*input_read(char *input, int *j);
char	*delete_quotation(char *input);
char	*opt_read(char *input, int *j);
#endif
