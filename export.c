/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:20:25 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/22 17:26:00 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **env, char *name)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], name, ft_strlen(name)) != 0)
		i++;
	if (!env[i])
		return ;
	free(env[i]);
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

char	**copy_environment(char **old, int ind)
{
	char	**new;
	int		i;

	i = 0;
	while (old[i])
		i++;
	if (ind == 1)
		new = malloc(sizeof(char *) * (i + 1));
	if (ind == 0)
		new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	if (ind == 0)
		del_env(old);
	return (new);
}

int	add_var(char ***ev, char *arg, int i)
{
	char **env;

	env = copy_environment(*ev, 0);
	env[i] = ft_strdup(arg);
	env[i + 1] = NULL;
	*ev = env;
	return (0);
}

int	export(char ***ev, t_cmd *cmd)
{
	int	i;
	char	*name;
	char	**env;

	i = 0;
	env = *ev;
	while (cmd->arg[i] && cmd->arg[i] != '=')
		i++;
	if (!cmd->arg[i] || !cmd->arg[i + 1])
	{
		printf("Invalid argument format for export\n");
		return (-1);
	}
	name = ft_substr(cmd->arg, 0, i - 1);
	while (env[i] && ft_strncmp(env[i], name, ft_strlen(name)))
		i++;
	free(name);
	if (!env[i])
		return(add_var(ev, cmd->arg, i));
	else
	{
		free(env[i]);
		env[i] = ft_strdup(cmd->arg);
		return (0);
	}
}