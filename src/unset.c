/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:17:55 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*ft_name(char *str)
{
	t_count	c;

	c.i = 0;
	while (str[c.i])
	{
		if (str[c.i] == '=' && !quoted(str, c.i))
			return (ft_substr(str, 0, c.i));
		c.i++;
	}
	return (ft_strdup(str));
}

int	ft_unset(char **env, char **cmd)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		while (env[j] && ft_strncmp(env[j], cmd[i], ft_strlen(cmd[i])) != 0)
			j++;
		if (env[j])
		{
			free(env[j]);
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
		}
		j = 0;
		i++;
	}
	return (0);
}
