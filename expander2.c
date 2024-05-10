/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:09 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/10 19:11:15 by teichelm         ###   ########.fr       */
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
		i = ft_strlen(var) + 1;
		while (arg[i + index])
		{
			arg[index] = arg[i + index];
			index++;
		}
		arg[index] = 0;
		return (arg);
	}
	result = paste_var(index, arg, var, env);
	free(var);
	free(arg);
	return (result);
}

int	ft_size(char *i)
{
	t_count	c;

	c.i = 0;
	c.quote_count = 0;
	c.count = 0;
	while (i[c.i])
	{
		if (i[c.i] == 34 && c.count % 2 == 0)
			c.quote_count++;
		if (i[c.i] == 39 && c.quote_count % 2 == 0)
			c.count++;
		c.i++;
	}
	return (c.i - c.count - c.quote_count + 1);
}

char	*delete_quotation(char *i, int a)
{
	t_count	c;
	char	*result;

	result = malloc(sizeof(char) * ft_size(i));
	c.count = 0;
	c.quote_count = 0;
	c.j = 0;
	while (a < ft_size(i))
	{
		while ((i[a + c.j] == 34 && c.count % 2 == 0))
		{
			c.quote_count++;
			c.j++;
		}
		while ((i[a + c.j] == 39 && c.quote_count % 2 == 0))
		{
			c.count++;
			c.j++;
		}
		result[a] = i[a + c.j];
		a += 1;
	}
	result[a - 1] = 0;
	free(i);
	return (result);
}

char	*rm(char *str)
{
	char	*temp;

	if (str && str[0])
	{
		temp = str;
		str = ft_strtrim(str, " 	");
		free(temp);
		str = delete_quotation(str, 0);
	}
	return (str);
}

int	remove_quotation(t_cmd *cmd)
{
	if (cmd->input)
		cmd->input = rm(cmd->input);
	if (cmd->cmd)
		cmd->cmd = rm(cmd->cmd);
	if (cmd->arg)
		cmd->arg = rm(cmd->arg);
	if (cmd->ifile)
		cmd->ifile = rm(cmd->ifile);
	if (cmd->ofile)
		cmd->ofile = rm(cmd->ofile);
	return (0);
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
