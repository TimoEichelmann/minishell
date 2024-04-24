/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:44 by snegi             #+#    #+#             */
/*   Updated: 2024/04/24 15:02:01 by teichelm         ###   ########.fr       */
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
	char  	*input;
	int	pipe_num;
	int	exit_status;
	char	**env;
}	t_basic;


typedef struct s_shell {
	int	file;
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
	// char	*ired;
	// char	*iredfile;
	// char	*ored;
	// char	*oredfile;
	// char	*ireda;
	// char	*iredfilea;
	// char	*oreda;
	// char	*oredfilea;
	char	*file;
	char	*token; //pipes
}	t_cmd;


typedef struct s_env {
	char	*var;
}	t_env;


int	maintain_cd(char *input, char **env);
char	*get_command(char **path, char *command);
int	main_exec(t_basic *basic, t_cmd *cmd );
int    our_functions(t_cmd *cmd, t_basic *basic);
void    free_memory(t_shell *shell);
int	ft_env(char **env);
void	del_env(char **env);
char	*ft_getenv(char **env, char *name);
char	**init_env(char **ev);
int	substr_len(char *substr);
void	free_cmd(t_cmd *cmd);
void	ft_exit(char **env);
char	*cmd_read(char *input, int *j);
int	space_check(char *input, int ind);
int	is_token(char *c);
char	*arg_read(char *input, int *j);
char	*token_read(char *input, int *j, char **file);
t_cmd	*parser(char *input, char **env, int ex_status);
int	unclosed_quotes(char *input);
int	iterate_quotes(char *input, int ind, int i);
char	**copy_environment(char **old, int ind);
void	command_parser(char	*input, t_cmd **cmd, int cmd_count);
int	command_counter(char *input);
int	command_lexer(t_cmd *c, char **env, int ex_status);
int	own_lexer(t_cmd *cmd, int ind, char **env, int ex_status);
char	*expander(char *str, char **env, int ex_status);
char	*exchange(char *arg, int index, char **env);
int	env_lexer(t_cmd cmd);
int	own_check(char *cmd);
char	*input_read(char *input, int *j);
char	*delete_quotation(char *input);
char	*opt_read(char *input, int *j, int ind);
int	echo(t_cmd *cmd, t_basic *basic);
int	ft_unset(char **env, char *name);
int	add_var(char ***ev, char *arg, int i);
int	ft_export(char ***ev, char *arg);
int	token_check(t_cmd *cmd, t_shell *shell);

#endif
