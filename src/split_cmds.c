/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:13:39 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd[i].end)
		i++;
	return (i - 1);
}

int	split_size(char *str, int *q1, int *q2, char ch)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	c.count = 1;
	if (!str)
		return (0);
	while (str && str[c.i])
	{
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (str[c.i] == ch && ((c.qcount39 % 2 || c.qcount34 % 2) != 1))
			c.count++;
		c.i++;
	}
	if (q1 && q2)
	{
		*q1 = 0;
		*q2 = 0;
	}
	return (c.count);
}

char	**split_cmds(char *str, char ch)
{
	t_count	c;
	char	**result;

	c.i = 0;
	c.j = 0;
	c.count = 0;
	result = malloc(sizeof(char *)
			* (split_size(str, &c.qcount39, &c.qcount34, ch) + 1));
	while (str && str[c.i])
	{
		if (str[c.i] == ch && !quoted(str, c.i))
		{
			result[c.count++] = ft_substr(str, c.j, c.i - c.j);
			while (str[c.i + 1] == ch)
				c.i++;
			c.j = c.i + 1;
		}
		if (!str[c.i + 1] && str[c.i] != ' ')
			result[c.count++] = ft_substr(str, c.j, c.i - c.j + 1);
		c.i++;
	}
	result[c.count] = NULL;
	return (result);
}
