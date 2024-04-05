/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:44 by snegi             #+#    #+#             */
/*   Updated: 2024/04/05 12:26:27 by teichelm         ###   ########.fr       */
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

typedef struct s_env {
	char	*var;
}	t_env;


// char	**ft_split(char const *s, char c);
// char	*ft_strjoin(char const *s1, char const *s2);
// size_t	ft_strlcpy(char *dst, const char *src, size_t size);
// int	ft_strncmp(const char *s1, const char *s2, size_t n);
char *maintain_cd(char *input, char *promt) ;
// int	ft_strlen(const char *s);
// void    change_env(t_list *env, char *input/* , t_shell *shell */);
// void    remove_env(char **env, char *input);
void	ft_env(t_list *env);
void	del_env(t_list *env);
char	*ft_getenv(t_list *env, char *name);
t_list	*init_env(char **ev);
void	echo(char *input, t_list *env);
int	substr_len(char *substr);
// char	*ft_substr(const char *s, unsigned int start, unsigned int len);
#endif
