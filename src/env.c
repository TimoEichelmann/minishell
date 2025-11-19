/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:06 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**init_env(char **ev)
{
	char	**env;

	env = copy_environment(ev, 1);
	return (env);
}

int	solo_export(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

char	*ft_getenv(char **env, char *name)
{
	int		i;
	int		ind; 
	int		j;

	j = 0;
	i = 0;
	ind = 0;
	while (env[i] && ind == 0)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0)
			ind = 1;
		else
			i++;
	}
	if (!env[i])
		return (NULL);
	while (env[i][j] && env[i][j] != '=')
		j++;
	if (!env[i][j])
		return (NULL);
	return (env[i] + j + 1);
}

int	ft_env(char **env, t_cmd *cmd)
{
	int		i;

	i = 0;
	if (cmd->cmd[1])
	{
		printf("env: '%s' no such file or directory\n", cmd->cmd[i]);
		return (127);
	}
	while (env && env[i])
	{
		if (true_env(env[i]) == 0)
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	true_env(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i])
		return (-1);
	return (0);
}
