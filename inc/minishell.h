/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:44 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 14:53:02 by teichelm         ###   ########.fr       */
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
# include "../libft/libft.h"

static int	g_signum;

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

typedef struct s_cmd{
	char	**cmd;
	char	**red;
	int		end;
}	t_cmd;

typedef struct s_count {
	int	i;
	int	quote_count;
	int	qcount34;
	int	qcount39;
	int	q4;
	int	q9;
	int	count;
	int	count2;
	int	j;
}	t_count;

int		count_pipes(t_cmd *cmd);
char	**add_var(char **env, char *arg, int i);
int		modify_pwd(char **env, char *pwd);
char	**modify_env(char **ev, int j, int i, char **cmd);
char	*expander(char *str, char **env, int ex);
char	*expand_variable(char **env, int *i, char *str);
int		var_len(char *var);
char	*paste_exit_status(char *str, int ex, int i);
char	**cpy_array(char **dest);
int		array_size(char **arr);
int		realloc_redirect(char ***red);
int		redirect_need(char *str);
int		split_size(char *str, int *q1, int *q2, char ch);
char	**split_cmds(char *str, char ch);
char	*remover(char *s);
char	*free_strtrim(char *s);
char	not_space(char *str);
void	free_cmd(t_cmd *cmd);
char	*paste_str(char *str, char *fill, int start, int len);
char	*cut_str(char *str, int start, int len);
char	**redirect(char **s, char **red);
char	*cut_redirect(char *str, int i, char ch);
char	**parse_redirect(char *str, char **red, int i);
char	redirect_type(char *str);
char	*filename(char *str, int i);
int		var_len(char *var);
char	*paste_exit_status(char *str, int ex, int i);
char	*expand_variable(char **env, int *i, char *str);
char	*expander(char *str, char **env, int ex);
void	del_env(char **env);
int		modify_pwd(char **env, char *pwd);
char	*ft_name(char *str);
int		ft_unset(char **env, char **cmd);
int		quoted(char *str, int i);
int		solo_export(char **env);
int		ft_export(char ***ev, char **cmd, char *pwd);
char	**init_env(char **ev);
char	*ft_getenv(char **env, char *name);
void	del_env(char **env);
int		ft_env(char **env, t_cmd *cmd);
void	ft_pwd(t_basic *basic);
int		maintain_cd(char **cmd, char **env);
int		change_pwd(char **env);
int		echo(t_cmd *cmd);
int		check_command(char *in);
t_cmd	*creator(char *input, char **env, int exit_status);
void	free_cmd(t_cmd *cmd);
char	**init_env(char **ev);
void	del_env(char **env);
void	ft_exit(t_basic *basic, t_cmd *cmd);
char	**copy_environment(char **old, int ind);
int		true_env(char *env);
void	single_exec(t_cmd *cmd, t_basic *basic);
int		our_functions(t_cmd *cmd, t_basic *basic);
void	free_memory(t_shell *shell);
char	*ft_getenv(char **env, char *name);
void	handle_exec_sig(int sig);
void	token_check(t_cmd *cmd, t_shell *shell);
int		main_exec(t_basic *basic, t_cmd *cmd );
void	get_shelldata(t_shell *shell, t_basic *basic, t_cmd *cmd);
void	print_shellerror(char *str, char *cmd, t_shell *shell, int exit_st);
int		change_pwd(char **env);
void	free_delimiter(char **del);
#endif
