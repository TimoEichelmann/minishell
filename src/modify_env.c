/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 13:15:16 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	change_pwd(char **env)
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
	ft_export(&env, NULL, pwd);
	ft_export(&env, NULL, old_pwd);
	free(pwd);
	free(old_pwd);
	return (0);
}

int	modify_pwd(char **env, char *pwd)
{
	int		i;
	char	*name;

	if (ft_strncmp(pwd, "PWD", 3) == 0)
		name = ft_substr(pwd, 0, 3);
	else
		name = ft_substr(pwd, 0, 6);
	i = 0;
	while (env[i] && ft_strncmp(env[i], name, ft_strlen(name)) != 0)
		i++;
	free(name);
	free(env[i]);
	env[i] = ft_strdup(pwd);
	return (0);
}

char	**modify_env(char **ev, int j, int i, char **cmd)
{
	int	r;

	r = 0;
	if (!ev[j])
		ev = add_var(ev, cmd[i], j);
	else
	{
		while (cmd[i][r] && cmd[i][r] != '=')
			r++;
		if (!cmd[i][r])
			return (ev);
		free(ev[j]);
		ev[j] = ft_strdup(cmd[i]);
	}
	return (ev);
}
