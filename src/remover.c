/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remover.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:14:14 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*free_strtrim(char *s)
{
	char	*tmp;

	tmp = s;
	s = ft_strtrim(s, " ");
	free(tmp);
	return (s);
}

int	quoted(char *str, int i)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (str[c.i] && c.i < i)
	{
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		c.i++;
	}
	if ((c.qcount39 % 2 || c.qcount34 % 2) == 1)
		return (1);
	return (0);
}

char	*remover(char *s)
{
	t_count	c;

	c.i = 0;
	c.q4 = 0;
	c.q9 = 0;
	while (s && s[c.i])
	{
		if (s[c.i] == 39 && c.q4 % 2 != 1)
			c.q9++;
		if (s[c.i] == 34 && c.q9 % 2 != 1)
			c.q4++;
		if ((s[c.i] == 34 && c.q9 % 2 != 1) || (s[c.i] == 39 && c.q4 % 2 != 1))
			s[c.i] = 127;
		c.i++;
	}
	c.i = 0;
	while (s && s[c.i])
	{
		while (s && s[c.i] && s[c.i] == 127)
			s = cut_str(s, c.i, 1);
		if (c.i >= ft_strlen(s))
			c.i = ft_strlen(s) - 1;
		c.i++;
	}
	return (s);
}
