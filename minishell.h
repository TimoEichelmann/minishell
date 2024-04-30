/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:44 by snegi             #+#    #+#             */
/*   Updated: 2024/04/30 14:53:29 by teichelm         ###   ########.fr       */
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
	int	file;
	int	ofile;
	char	*path;
	char	**command_path;
	char	**command_arg;
	char	*command;
}	t_shell;

typedef	struct s_cmd {
	char	*cmd;
	char	*input;
	char	*arg;
	int		token;
	int		ired;
	int		ored;
	char	*ifile;
	char	*ofile;
}	t_cmd;

typedef	struct s_count {
	int	i;
	int	quote_count;
	int	count;
	int	count2;
	int	j;
} t_count;

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

#endif
