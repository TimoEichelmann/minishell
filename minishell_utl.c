/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:31:43 by snegi             #+#    #+#             */
/*   Updated: 2024/05/14 12:30:36 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(char **env)
{
	char	*pwd;
	char	*old_pwd;
	char	*temp;

	pwd = getcwd(NULL, 0);
	old_pwd = ft_getenv(env, "PWD");
	temp = pwd;
	pwd = ft_strjoin("PWD=", pwd);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(temp);
	ft_export(&env, pwd);
	ft_export(&env, old_pwd);
	free(pwd);
	free(old_pwd);
}

int	maintain_cd(char *input, char **env)
{
	int	i;

	i = 0;
	while (*input != '\0' && *input == ' ')
		input++;
	if (!*input)
		input = ft_getenv(env, "HOME");
	while (input[i])
	{
		if (input[i] == ' ')
		{
			printf("too many arguments\n");
			return (1);
		}
		i++;
	}
	if (chdir(input) != 0)
	{
		perror("chdir");
		return (1);
	}
	change_pwd(env);
	return (0);
}

void	ft_pwd(t_basic *basic)
{
	char	**ev;

	ev = basic->env;
	while (*ev && ev[0] != NULL)
	{
		if (strncmp(*ev, "PWD=", 4) == 0)
		{
			printf("%s\n", *ev + 4);
			return ;
		}
		ev++;
	}
	printf("PWD not found\n");
}
