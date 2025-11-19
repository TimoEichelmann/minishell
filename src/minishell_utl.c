/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:31:43 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_delimiter(char **del)
{
	int	i;

	i = 0;
	while (del[i])
	{
		free(del[i]);
		i++;
	}
	free(del);
}

int	change_dir(char **cmd, char **env, char *input)
{
	if (!cmd[1] || (ft_strncmp(cmd[1], "~\0", 2) == 0))
	{
		input = ft_getenv(env, "HOME");
		if (input == NULL)
		{
			printf("Home is not set\n");
			return (1);
		}
	}
	if (cmd[1] && ft_strncmp(cmd[1], "-\0", 2) == 0)
	{
		input = ft_getenv(env, "OLDPWD");
		if (input == NULL)
		{
			printf("OLDPWD is not set\n");
			return (1);
		}
	}
	if (chdir(input) != 0)
	{
		perror("chdir");
		return (1);
	}
	return (0);
}

int	maintain_cd(char **cmd, char **env)
{
	int		i;
	char	*input;

	i = 1;
	while (cmd[i] && cmd[i] != NULL)
		i++;
	if (i > 2)
	{
		printf("too many arguments\n");
		return (1);
	}
	input = cmd[1];
	if (change_dir(cmd, env, input) == 1)
		return (1);
	return (change_pwd(env));
}

void	ft_pwd(t_basic *basic)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	basic->exit_status = 0;
}

void	print_shellerror(char *str, char *cmd, t_shell *shell, int exit_st)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, str, ft_strlen(str));
	free_memory(shell);
	exit(exit_st);
}
