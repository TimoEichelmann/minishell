/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:44:55 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/03 14:45:22 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lexer(char *input)
{
	int	cmd_num;
	char	**splitted;
	int		i;

	i = 0;
	cmd_num = count_cmds(input);
	splitted = ft_split(input, '|');
	while (splitted[i])
		i++;
	if (cmd_num != 1 && cmd_num != i - 1)
	{
		print_check(-2, splitted);
		return (NULL);
	}
	if (checks(splitted) == -1)
		return (NULL);
	return (splitted);
}

char	*cmd_read(char *input, int *j)
{
	char	*result;
	int		i;
	
	i = 0;
	result = word(input + *j);
	while (result[i] == ' ' || result[i] == '	')
		i++;
	*j += ft_strlen(result) + i;
	return (result);
}

int	check_true_arg(char *input)
{
	t_count c;

	c.i = 0;
	c.quote_count = 0;
	if (!input || !input[0])
		return (-1);
	while (input[c.i])
	{
		if (input[c.i] == 34 || input[c.i] == 39)
			c.quote_count++;
		if (c.quote_count % 2 != 1 && (input[c.i] == '<' || input[c.i] == '>'))
			return (-1);
		c.i++;
	}
	return (0);
}