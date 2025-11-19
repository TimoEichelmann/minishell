/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:11:49 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	redirect_need(char *str)
{
	t_count	c;

	c.i = 0;
	c.q4 = 0;
	c.q9 = 0;
	while (str[c.i])
	{
		if (str[c.i] == 39 && c.q4 % 2 != 1)
			c.q9++;
		if (str[c.i] == 34 && c.q9 % 2 != 1)
			c.q4++;
		if ((str[c.i] == '<' || str[c.i] == '>')
			&& (c.q4 % 2 || c.q9 % 2) != 1)
			return (1);
		c.i++;
	}
	return (0);
}

int	realloc_redirect(char ***red)
{
	char	**r;
	char	**r2;
	int		i;

	if (!*red)
	{
		*red = malloc(sizeof(char *) * 2);
		return (0);
	}
	i = 0;
	r = *red;
	while (r[i])
		i++;
	*red = malloc(sizeof(char *) * (i + 1));
	i = 0;
	r2 = *red;
	while (r[i])
	{
		r2[i] = r[i];
		i++;
	}
	free(r);
	return (i);
}

int	array_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**cpy_array(char **dest)
{
	int		i;
	char	**temp;

	i = 0;
	temp = dest;
	dest = malloc(sizeof(char *) * (array_size(dest) + 2));
	while (temp[i])
	{
		dest[i] = temp[i];
		i++;
	}
	free(temp);
	dest[i] = NULL;
	return (dest);
}
