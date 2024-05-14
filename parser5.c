/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:11:07 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/14 12:11:29 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_need(char *in, int *ineed, int *oneed)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (in[c.i])
	{
		if (in[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (in[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (in[c.i] == '<' && c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1)
			*ineed = c.i;
		if (in[c.i] == '>' && c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1)
			*oneed = c.i;
		if ((in[c.i] == '<' || in[c.i] == '>') && c.qcount34 % 2 != 1
			&& c.qcount39 % 2 != 1 && (in[c.i + 1] == '<'
				|| in[c.i + 1] == '>'))
			c.i++;
		c.i++;
	}
	if (*oneed > 0 || *ineed > 0)
		return (1);
	return (0);
}
