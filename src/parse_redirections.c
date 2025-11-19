/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:10:56 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*filename(char *str, int i)
{
	t_count	c;

	c.i = i;
	c.q4 = 0;
	c.q9 = 0;
	while (str[c.i])
	{
		if (str[c.i] == 39 && c.q4 % 2 != 1)
			c.q9++;
		if (str[c.i] == 34 && c.q9 % 2 != 1)
			c.q4++;
		if ((str[c.i] == ' ' || str[c.i] == '	' || str[c.i] == '<'
				|| !str[c.i + 1] || str[c.i] == '>')
			&& (c.q4 % 2 || c.q9 % 2) != 1)
		{
			if (!str[c.i + 1])
				c.i += 1;
			return (ft_substr(str, i, c.i - i));
		}
		c.i++;
	}
	return (ft_substr(str, i, c.i + 1));
}

char	redirect_type(char *str)
{
	if (str[0] == '>' && str[1] != '>')
		return ('1');
	if (str[0] == '>' && str[1] == '>')
		return ('2');
	if (str[0] == '<' && str[1] != '<')
		return ('3');
	if (str[0] == '<' && str[1] == '<')
		return ('4');
	return (0);
}

char	**parse_redirect(char *str, char **red, int i)
{
	char	c;
	char	ind;
	int		size;

	ind = redirect_type(str + i);
	c = str[i];
	while (str[i] == c)
		i++;
	while (str[i] == ' ')
		i++;
	if (red)
		red = cpy_array(red);
	else
	{
		red = malloc(sizeof(char *) * 2);
		red[0] = NULL;
	}
	size = array_size(red);
	red[size + 1] = NULL;
	red[size] = filename(str, i);
	red[size] = paste_str(red[size], " ", 0, 1);
	red[size] = paste_str(red[size], &ind, 0, 1);
	return (red);
}

char	*cut_redirect(char *str, int i, char ch)
{
	t_count	c;

	c.i = i;
	c.q4 = 0;
	c.q9 = 0;
	while (str[c.i] == ch)
		c.i++;
	while (str[c.i] == ' ')
		c.i++;
	while (str[c.i])
	{
		if (str[c.i] == 39 && c.q4 % 2 != 1)
			c.q9++;
		if (str[c.i] == 34 && c.q9 % 2 != 1)
			c.q4++;
		if (((c.q4 % 2 || c.q9 % 2) != 1) && (str[c.i] == ' ' || !str[c.i + 1]
				|| str[c.i] == '	' || str[c.i] == '<' || str[c.i] == '>'))
		{
			if (!str[c.i + 1])
				c.i += 1;
			return (cut_str(str, i, c.i - i));
		}
		c.i++;
	}
	return (str);
}

char	**redirect(char **s, char **red)
{
	t_count	c;
	char	*str;

	c.i = 0;
	str = *s;
	while (str && str[c.i])
	{
		if ((str[c.i] == '<' || str[c.i] == '>') && !quoted(str, c.i))
		{
			red = parse_redirect(str, red, c.i);
			str = cut_redirect(str, c.i, str[c.i]);
			if (c.i != 0 && str[c.i] == ' ' && str[c.i - 1] == ' ')
				str = cut_str(str, c.i, 1);
			if (ft_strlen(str) < c.i)
				c.i = ft_strlen(str);
			c.i--;
		}
		c.i++;
	}
	*s = str;
	return (red);
}
