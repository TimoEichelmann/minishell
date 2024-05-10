/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:39:31 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/10 12:57:52 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotation(char **splitted)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	c.count = 0;
	while (splitted[c.i])
	{
		while (splitted[c.i][c.count])
		{
			if (splitted[c.i][c.count] == 34 && c.qcount39 % 2 != 1)
				c.qcount34++;
			if (splitted[c.i][c.count] == 39 && c.qcount34 % 2 != 1)
				c.qcount39++;
			c.count++;
		}
		if (c.qcount39 % 2 == 1 || c.qcount34 % 2 == 1)
			return (-1);
		c.count = 0;
		c.i++;
	}
	return (0);
}

void	free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted && splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

int	check_empty(char **splitted)
{
	t_count	c;

	c.i = 0;
	c.count = 0;
	while (splitted[c.i])
	{
		while (splitted[c.i][c.count] && (splitted[c.i][c.count] == '	'
				|| splitted[c.i][c.count] == ' '))
			c.count++;
		if (c.count == ft_strlen(splitted[c.i]))
			return (-2);
		c.i++;
		c.count = 0;
	}
	return (0);
}

int	check_redirections_loop(char *s, int c1, int c2, int quote_count)
{
	int	j;

	j = 0;
	while (s[j])
	{
		if (s[j] == 34 || s[j] == 39)
			quote_count++;
		if (s[j] == '>' && quote_count % 2 != 1)
		{
			if (s[j + 1] == '>' && s[j + 2])
				j++;
			c1 += 1;
		}
		if (s[j] == '<' && quote_count % 2 != 1)
		{
			if (s[j + 1] == '<' && s[j + 2])
				j++;
			c2 += 1;
		}
		j++;
	}
	if (c1 > 1 || c2 > 1)
		return (-1);
	return (0);
}

int	before(char *str, int i)
{
	if (!str[i + 1])
	{
		free(str);
		return (-1);
	}
	if (str[i - 1] == ' ' || str[i - 1] == '	')
		return (1);
	return (0);
}
