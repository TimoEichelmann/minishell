/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:20:25 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	**add_var(char **env, char *arg, int i)
{
	env = copy_environment(env, 0);
	env[i] = ft_strdup(arg);
	env[i + 1] = NULL;
	return (env);
}

int	alnumcheck(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]))
		return (1);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (1);
		i++;
	}
	return (0);
}

char	**export_args(char **ev, char **cmd)
{
	int		i;
	int		j;
	char	*name;

	i = 1;
	j = 0;
	while (cmd[i])
	{
		while (cmd[i] && alnumcheck(cmd[i]) == 1)
			i++;
		if (cmd[i])
		{
			name = ft_name(cmd[i]);
			while (ev[j] && ft_strncmp(ev[j], name, ft_strlen(name)) != 0)
				j++;
			free(name);
			ev = modify_env(ev, j, i, cmd);
			j = 0;
			i++;
		}
	}
	return (ev);
}

int	ft_export(char ***ev, char **cmd, char *pwd)
{
	int	exit;
	int	i;

	exit = 0;
	i = 1;
	if (!cmd)
		return (modify_pwd(*ev, pwd));
	if (!cmd[1])
		return (solo_export(*ev));
	while (cmd[i])
	{
		if (alnumcheck(cmd[i]) == 1)
		{
			printf("minishell: export '%s': not a valid identifier\n", cmd[i]);
			exit = 1;
		}
		i++;
	}
	*ev = export_args(*ev, cmd);
	return (exit);
}
