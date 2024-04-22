/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:24:40 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/22 17:34:22 by teichelm         ###   ########.fr       */
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
	if (!input[*j])
		return (NULL);
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	' && i < is_token(input + *j))
		i++;
	result = ft_substr(input, *j, i);
	*j = *j + i;
	return (result);
}

char	*opt_read(char *input, int *j)
{
	int	ind;
	int	i;

	ind = 0;
	i = 0;
	while ()
	
}

// int	space_check(char *input, int ind)
// {
// 	int	i;

// 	i = 0;
// 	if (ind == 0)
// 	{
// 		if (input[i + 1] && input[i - 1] && (input[i + 1] == ' '
// 			|| input[i + 1] == '	') && (input[i - 1] == ' '
// 			|| input[i - 1] == '	'))
// 			return (0);
// 		if (!input[i + 1] && (input[i - 1] == ' ' || input[i - 1] == '	'))
// 			return (0);
// 		return (1);
// 	}
// 	if (input[i + 2] && (input[i - 1] == ' ' || input[i - 1] == '	')
// 		&& (input[i + 2] == ' ' || input[i + 2] == '	'))
// 		return (0);
// 	if (!input[i + 2] && (input[i - 1] == '	' || input[i + 2] == ' '))
// 		return (0);
// 	return (1);
// }

int	is_token(char *c)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (c[i])
	{
		if (c[i] == 34 || c[i] == 39)
			quote_count++;
		if ((c[i] == '<' || c[i] == '>' || c[i] == '|') &&
				quote_count % 2 != 1)
			return (i);
		if ((c[i] == '<' && c[i + 1] == '<'
			&& quote_count % 2 != 1)
				|| (c[i] == '>' && c[i + 1] == '>'
					&& quote_count % 2 != 1))
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

char	*input_read(char *input, int *j)
{
	int	i;
	int	token;
	char *result;

	i = 0;
	while (input[i + *j] == ' ' || input[i + *j] == '	')
		i++;
	token = (is_token(input + *j + i));
	result = ft_substr(input, *j + i, token);
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
	while (input[i + *j] && (input[i + *j] == '|' || input[i + *j] == '>' || input[i + *j] == '<'))
		i++;
	result = ft_substr(input, *j, i);
	*j += i;
	return (result);
}
