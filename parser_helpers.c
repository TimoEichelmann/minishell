/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:24:40 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/15 16:56:54 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	')
		i++;
	result = ft_substr(input, *j, i);
	*j = *j + i;
	return (result);
}

char	*opt_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	if (input[*j] != '-')
		return (NULL);
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	')
		i++;
	result = ft_substr(input, *j, i);
	*j += i;
	return (result);
}

int	space_check(char *input, int ind)
{
	int	i;

	i = 0;
	if (ind == 0)
	{
		if (input[i + 1] && input[i - 1] && (input[i + 1] == ' '
			|| input[i + 1] == '	') && (input[i - 1] == ' '
			|| input[i - 1] == '	'))
			return (0);
		if (!input[i + 1] && (input[i - 1] == ' ' || input[i - 1] == '	'))
			return (0);
		return (1);
	}
	if (input[i + 2] && (input[i - 1] == ' ' || input[i - 1] == '	')
		&& (input[i + 2] == ' ' || input[i + 2] == '	'))
		return (0);
	if (!input[i + 2] && (input[i - 1] == '	' || input[i + 2] == ' '))
		return (0);
	return (1);
}

int	is_token(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if ((c[i] == '<' || c[i] == '>' || c[i] == '|') &&
			space_check(c + i, 0) == 0)
			return (i);
		if ((c[i] == '<' && c[i + 1] == '<' &&
			space_check(c + i, 1) == 0) || (c[i] == '>' &&
				c[i + 1] == '>' && space_check(c + i, 1) == 0))
			return (i);
		i++;
	}
	if (!c[i])
		return (i);
	return (0);
}

char	*arg_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	if (!input[*j])
		return (NULL);
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	if (!input[*j])
		return (NULL);
	while (i < is_token(input + *j))
		i++;
	if (i == 0)
		return (NULL);
	result = ft_substr(input, *j, i);
	*j += i;
	return (result);
}



char	*token_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	if (!input[*j])
		return (NULL);
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	')
		i++;
	// if (input[i + *j] == ' ' || input[i + *j] == '	')
	// 	i--;
	result = ft_substr(input, *j, i);
	*j += i;
	return (result);
}