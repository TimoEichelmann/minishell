/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:06 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/19 17:21:37 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**init_env(char **ev)
{
	char	**env;

	env = copy_environment(env, 1);
	return (env);
}

int	substr_len(char *substr)
{
	int	i;

	i = 0;
	while (substr[i] && substr[i] != ' '
		&& substr[i] != 34 && substr[i] != 39 && substr[i] != '$')
		i++;
	return (i);
}

char	*ft_getenv(char **env, char *name)
{
	int		i;
	char	*c;
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

void	ft_env(char **env)
{
	char 	*c;
	int		i;

	i = 0;
	while (env)
	{
		c = env->c;
		printf("%s\n", c);
		env = env->next;
	}
}