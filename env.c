/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:06 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/14 12:05:10 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (env[i][j] != '=')
		j++;
	return (env[i] + j + 1);
}

void	del_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

int	ft_env(char **env)
{
	int		i;

	i = 0;
	while (env && env[i])
	{
		if (true_env(env[i]) == 0)
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
