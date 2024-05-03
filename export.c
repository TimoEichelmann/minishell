/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:20:25 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/03 13:42:03 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **env, char *name)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], name, ft_strlen(name)) != 0)
		i++;
	if (!env[i])
		return (-1);
	free(env[i]);
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
	return (0);
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
	char	**env;

	env = copy_environment(*ev, 0);
	env[i] = ft_strdup(arg);
	env[i + 1] = NULL;
	*ev = env;
	return (0);
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

int	bad_assignment(void)
{
	printf("%s\n", "minishell: bad assignment");
	return (-1);
}

int	ft_export(char ***ev, char *arg)
{
	int		i;
	char	*name;
	char	**env;

	i = 0;
	env = *ev;
	if (!arg)
		return (solo_export(env));
	while (arg[i] && arg[i] != '=')
		i++;
	if ((arg[i] == '=' && (arg[i + 1] == ' ' || arg[i + 1] == '	'
			|| arg[i - 1] == ' ' || arg[i - 1] == '	')) || !arg[i])
		return (bad_assignment());
	name = ft_substr(arg, 0, i);
	while (env[i] && ft_strncmp(env[i], name, ft_strlen(name)) != 0)
		i++;
	free(name);
	if (!env[i])
		return (add_var(ev, arg, i));
	else
	{
		free(env[i]);
		env[i] = ft_strdup(arg);
		return (0);
	}
}