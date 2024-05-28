/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:44 by snegi             #+#    #+#             */
/*   Updated: 2024/05/28 16:31:36 by teichelm         ###   ########.fr       */
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
	char	**cmd;
	int		end;
	char 	**red;
}	t_cmd;

typedef struct s_count {
	int	i;
	int	quote_count;
	int	qcount34;
	int	qcount39;
	int	count;
	int	count2;
	int	j;
}	t_count;

void	print_error(char *str);
void	ft_exit(t_basic *basic, t_cmd *cmd);
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
int		env_lexer(t_cmd cmd);
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
int		print_check(int ind, char **splitted);
int		checks(char **splitted);
int		own_check(char *cmd);
char	**lexer(char *input);
char	*cmd_read(char *input, int *j);
void	free_cmd(t_cmd *cmd);
void	get_shelldata(t_shell *shell, t_basic *basic, t_cmd *cmd);
int		bad_assignment(void);
int		true_env(char *env);
int		not_identifier(char *arg);
int		solo_export(char **env);
int		splitted_size(char *input);
char	*splitted_string(char *input, int *j);
void	ft_pwd(t_basic *basic);

#endif
