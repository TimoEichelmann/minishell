/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:09 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/04 22:45:56 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exchange(char *arg, int index, char **env)
{
	char	*var;
	char	*result;
	int		i;

	i = 0;
	var = ft_substr(arg, index + 1, substr_len(arg + index + 1));
	if (!ft_getenv(env, var))
	{
		free(var);
		free(arg);
		return (NULL);
	}
	result = paste_var(index, arg, var, env);
	free(var);
	free(arg);
	return (result);
}

char	*delete_quotation(char *i)
{
	t_count	c;
	char	*result;

	c.i = 0;
	c.j = 0;
	c.count = 0;
	while (i[c.i])
	{
		if (i[c.i] == 34 || i[c.i] == 39)
			c.count++;
		c.i++;
	}
	result = malloc(sizeof(char) * (ft_strlen(i) - c.count + 1));
	c.i = 0;
	while (i[c.i + c.j])
	{
		while (i[c.i + c.j] && (i[c.i + c.j] == 34 || i[c.i + c.j] == 39))
			c.j++;
		result[c.i] = i[c.i + c.j];
		if (i[c.i + c.j])
			c.i++;
	}
	result[c.i] = 0;
	free(i);
	return (result);
}

int	remove_quotation(t_cmd *cmd)
{
	char	*temp;

	if (cmd->input)
	{
		cmd->input = delete_quotation(cmd->input);
		temp = cmd->input;
		cmd->input = ft_strtrim(cmd->input, " 	");
		free(temp);
	}
	if (cmd->cmd)
	{
		cmd->cmd = delete_quotation(cmd->cmd);
		temp = cmd->cmd;
		cmd->cmd = ft_strtrim(cmd->cmd, " 	");
		free(temp);
	}
	if (cmd->arg)
	{
		cmd->arg = delete_quotation(cmd->arg);
		temp = cmd->arg;
		cmd->arg = ft_strtrim(cmd->arg, " 	");
		free(temp);
	}
	return (0);
}

void	expansion(t_cmd *cmd, char **env, int ex)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
	{
		cmd[i].arg = expander(cmd[i].arg, env, ex);
		cmd[i].input = expander(cmd[i].input, env, ex);
		remove_quotation(&cmd[i]);
		i++;
	}
}

char	*paste_var(int index, char *arg, char *var, char **env)
{
	char	*result;
	int		i;

	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(arg) - ft_strlen(var)
				+ ft_strlen(ft_getenv(env, var))));
	while (i < index)
	{
		result[i] = arg[i];
		i++;
	}
	index += ft_strlcpy(result + i, ft_getenv(env, var),
			ft_strlen(ft_getenv(env, var)) + 1);
	i += ft_strlen(var) + 1;
	while (arg[i])
	{
		result[index] = arg[i];
		index++;
		i++;
	}
	result[index] = 0;
	return (result);
}
