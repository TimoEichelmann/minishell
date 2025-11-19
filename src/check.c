/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:16:47 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_empty(char *in)
{
	int	i;

	i = 0;
	while (in[i] == ' ' || in[i] == '	')
		i++;
	if (ft_strlen(in) == i)
		return (2);
	i = 0;
	while (in[i])
	{
		if (in[i] == '|' && !quoted(in, i))
		{
			i++;
			while ((in[i] == ' ' || in[i] == '	' || in[i] == 34
					|| in[i] == 39) && in[i])
				i++;
			if (in[i] == '|' && !quoted(in, i))
				return (1);
			if (!in[i])
				return (0);
		}
		i++;
	}
	return (0);
}

int	check_quotation(char *splitted)
{
	t_count	c;

	c.i = 0;
	c.j = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (splitted[c.i])
	{
		if (splitted[c.i] == 34 && c.qcount39 % 2 != 1)
		{
			c.j = c.i;
			c.qcount34++;
		}
		if (splitted[c.i] == 39 && c.qcount34 % 2 != 1)
		{
			c.j = c.i;
			c.qcount39++;
		}
		c.i++;
	}
	if (c.qcount39 % 2 == 1 || c.qcount34 % 2 == 1)
		return (c.j);
	return (0);
}

int	error_print(int pos, char *in, int ind)
{
	printf("minishell: ");
	if (ind == 1)
		printf("parse error near '|'\n");
	if (ind == 2)
		printf("error at '%c'(col:%d) unclosed quotes\n", in[pos], pos + 1);
	if (ind == 3)
		printf("error at '%c'(col:%d), wrong redirection\n", in[pos], pos + 1);
	return (1);
}

int	check_redirection(char *in)
{
	t_count	c;

	c.i = 0;
	c.j = 0;
	while (in[c.i])
	{
		if (in[c.i] == '<' && !quoted(in, c.i))
		{
			while (in[c.i + c.j] == '<')
				c.j++;
			if (c.j > 2)
				return (c.i);
			c.j = 0;
		}
		if (in[c.i] == '>' && !quoted(in, c.i))
		{
			while (in[c.i + c.j] == '>')
				c.j++;
			if (c.j > 2)
				return (c.i);
			c.j = 0;
		}
		c.i++;
	}
	return (0);
}

int	check_command(char *in)
{
	if (check_empty(in) == 1)
		return (error_print(0, in, 1));
	if (check_empty(in) == 2)
		return (1);
	if (check_quotation(in))
		return (error_print(check_quotation(in), in, 2));
	if (check_redirection(in))
		return (error_print(check_redirection(in), in, 3));
	return (0);
}
