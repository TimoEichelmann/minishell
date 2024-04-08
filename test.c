/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:42:42 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/08 14:01:29 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	iterate_quotes(char *input, int ind, int i)
{
	int	quote_count;
	int	quote_check;

	quote_count = 0;
	quote_check = 0;
	while (input[i])
	{
		if (ind == 1 && input[i] == 34 || ind == 2 && input[i] == 39)
			quote_count++;
		i++;
	}
	i = 0;
	if (quote_count % 2 == 1)
	{
		if (quote_count == 1)
			quote_count++;
		while (quote_check != quote_count - 1)
		{
			if (ind == 1 && input[i] == 34 || ind == 2 && input[i] == 39)
				quote_check++;
			i++;
		}
		return (i);
	}
	return (-1);
}

int	unclosed_quotes(char *input)
{
	int	squote;
	int	dquote;
	int	i;

	i = 0;
	squote = iterate_quotes(input, 2, i);
	dquote = iterate_quotes(input, 1, i);
	if (dquote == -1 && squote >= 0)
		return (squote);
	if (squote == -1 && dquote >= 0)
		return (dquote);
	if (dquote > squote && squote > 0)
		return (squote);
	if (squote > dquote && dquote > 0)
		return (dquote);
	if (squote == dquote)
		return (squote);
	return (0);
}

int	count_lines(int unclosed, char *input, int i, int line_count)
{
	int	dquote;
	int	squote;

	dquote = 0;
	squote = 0;
	while (input[i] && input[i] != unclosed)
	{
		if (dquote != 1 && squote != 1 && (input[i] == ' ' || input[i] == '	'))
			line_count++;
		if (input[i] == 34 && dquote == 0)
			dquote += 1;
		if (input[i] == 39 && squote == 0)
			squote += 1;
		if ((input[i] == 39 && squote == 1) || (input[i] == 34 && dquote == 1))
		{
			if (input[i] == 39)
				squote = 0;
			if (input[i] == 34)
				dquote = 0;
			line_count++;
		}
		printf("linec : %d, squote : %d dquote : %d i : %d\n", line_count, squote, dquote, i);
		i++;
	}
	return (line_count);
}

char	**parser(char *input)
{
	int	line_count;
	int	unclosed;
	int	i;

	i = 0;
	line_count = 0;
	unclosed = unclosed_quotes(input);
	line_count = count_lines(unclosed, input, i, line_count);
	printf("%d\n", line_count);
	return (NULL);
}

int main()
{
	char *p = readline(">");
	// printf("%d\n", unclosed_quotes(p));
	parser(p);
}