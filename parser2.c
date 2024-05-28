/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:44:41 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/28 13:51:42 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *input, int i)
{
	t_count	c;

	c.qcount34 = 0;
	c.qcount39 = 0;
	c.i = 0;
	if (input[i] != '|')
		return (-1);
	while (c.i < i)
	{
		if (input[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (input[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		c.i++;
	}
	if (c.qcount34 % 2 == 1 || c.qcount39 % 2 == 1)
		return (-1);
	return (0);
}

char	*arg_read(char *input, int ind, int *j)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	if (ind < 0)
		return (NULL);
	while (input[*j] == ' ')
		*j += 1;
	while (input[i + *j] && check_pipe(input, i + *j) != 0)
		i++;
	if (i > 0)
		result = ft_substr(input, *j, i);
	return (result);
}

char	*ft_return(char *str, int i)
{
	if (i == 0)
		return (NULL);
	return (str);
}

char	*delete_redirection(char *str, int i)
{
	int		j;
	char	*len;
	int		p;

	j = 0;
	while (str[i + j] == ' ' || str[i + j] == '<' || str[i + j] == '>')
		j++;
	len = word(str + i + j);
	p = ft_strlen(len) + j;
	while (str[i + p] == ' ')
		p++;
	free(len);
	if (i > 0 && str[i - 1] != ' ')
	{
		str[i] = ' ';
		p--;
		i++;
	}
	while (str[i + p])
	{
		str[i] = str[p + i];
		i++;
	}
	str[i] = 0;
	return (ft_return(str, i));
}

char	*remove_redirection(char *str)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (str && str[c.i])
	{
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if ((str[c.i] == '<' || str[c.i] == '>')
			&& c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1)
		{
			delete_redirection(str, c.i);
			c.i--;
		}
		c.i++;
	}
	return (str);
}
