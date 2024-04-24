/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:24:40 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/24 13:47:04 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//tokens passed withput space
//filenames for >> <<

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

char	*opt_read(char *input, int *j, int ind)
{
	int		i;

	i = 0;
	if (ind == 0)
		return (NULL);
	while (input[*j] == '	' || input[*j] == ' ')
		*j += 1;
	if (!input[*j])
		return (NULL);
	if (ft_strncmp(input + *j, "-n", 2) == 0 ||
			(input[*j] == 34 && ft_strncmp(input + *j + 1, "-n", 2) == 0
				&& input[*j + 3] == 34) || (input[*j] == 34
					&& ft_strncmp(input + *j + 1, "-n", 2) == 0
						&& input[*j + 3] == 34))
	{
		*j += 2;
		return (ft_strdup("-n"));
	}
	return (NULL);
}

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

char	*file_read(char *input, int *j)
{
	int	i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	while (input[*j + i] && input [*j + i] != '	' && input[*j + i] != '	')
		i++;
	result = ft_substr(input, *j, i);
	*j += i;
	return (result);
}

char	*token_read(char *input, int *j, char **file)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	if (!input[*j])
	{
		*file = NULL;
		return (NULL);
	}
	while (input[i + *j] && (input[i + *j] == '|' || input[i + *j] == '>' || input[i + *j] == '<'))
		i++;
	result = ft_substr(input, *j, i);
	if (input[i + *j - 1] == '<' || input[i + *j - 1] == '>')
	{
		*j += i;
		*file = file_read(input, j);
	}
	else
		*file = NULL;
	*j += i;
	return (result);
}
