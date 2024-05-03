/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:40:11 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/03 14:40:39 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(char *input)
{
	t_count	c;

	c.i = 0;
	c.quote_count = 0;
	c.count = 0;
	while (input[c.i])
	{
		if (input[c.i] == 34 || input[c.i] == 39)
			c.quote_count++;
		if (input[c.i] == '|' && c.quote_count % 2 != 1)
			c.count++;
		c.i++;
	}
	if (!input[c.i] && c.count == 0)
		return (1);
	else
		return (c.count);
}

char	*realloc_redirection(char *str, int i)
{
	char	*result;
	int		j;

	j = 0;
	if (before(str, i) == -1)
		return (NULL);
	if (before(str, i) == 1)
		return (str);
	else
		result = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = ' ';
	while (str[j])
	{
		result[j + 1] = str[j];
		j++;
	}
	result[j + 1] = '\0';
	free(str);
	return (result);	
}

int	parse_redirections(char	**str, int i)
{
	t_count	c;
	char	*s;

	c.i = 0;
	s = str[i];
	c.count = 0;
	c.quote_count = 0;
	while (s && s[c.i])
	{
		if (s[c.i] == 34 || s[c.i] == 39)
			c.quote_count++;
		if ((s[c.i] == '<' || s[c.i] == '>') && c.quote_count % 2 != 1 
				&& s[c.i - 1] != '<' && s[c.i - 1] != '>')
		{
			str[i] = realloc_redirection(s, c.i);
			c.i += c.count;
		}
		c.count = 0;
		if (!str[i])
			return (-1);
		s = str[i];
		c.i++;	
	}
	return (0);
}

int	check_redirections(char **s)
{
	t_count c;
	int		j;
	
	c.i = 0;
	c.quote_count = 0;
	c.count = 0;
	c.count2 = 0;
	c.j = 0;
	while (s[c.i])
	{
		j = check_redirections_loop(s[c.i], c.count, c.count2, c.quote_count);
		if (j == -1)
		{
			return (-3);
		}
		j = parse_redirections(s, c.i);
		if (j == -1)
		{
			return (-3);
		}
		c.i++;
	}
	return (0);
}

int	print_check(int ind, char **splitted)
{
	if (ind == -1)
		printf("parse error due to wrong quotation\n");
	if (ind == -2)
		printf("parse error due to empty command\n");
	if (ind == -3)
		printf("parse error due to wrong redirection\n");
	free_splitted(splitted);
	return (-1);
}
