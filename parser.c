/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:22:53 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/15 17:31:03 by teichelm         ###   ########.fr       */
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
		if ((ind == 1 && input[i] == 34) || (ind == 2 && input[i] == 39))
			quote_count++;
		i++;
	}
	i = 0;
	if (quote_count % 2 == 1)
	{
		while (quote_check != quote_count)
		{
			if ((ind == 1 && input[i] == 34) || (ind == 2 && input[i] == 39))
				quote_check++;
			i++;
		}
		return (i - 1);
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

t_cmd	*parser(char *input, t_list *env)
{
	t_cmd	*cmd;
	int			cmd_count;
	int			unclosed;

	unclosed = unclosed_quotes(input);
	if (unclosed != -1)
		return (NULL);
	cmd_count = command_counter(input);
	cmd = malloc(sizeof(t_cmd) * (cmd_count + 1));
	command_parser(input, &cmd, cmd_count);
	command_lexer(cmd, env);
	return (cmd);
}

void	command_parser(char	*input, t_cmd **cmd, int cmd_count)
{
	t_cmd	*c;
	int			i;
	int			j;

	j = 0;
	i  = 0;
	c = *cmd;
	while (i < cmd_count)
	{
		c[i].cmd = cmd_read(input, &j);
		c[i].option = opt_read(input, &j);
		c[i].arg = arg_read(input, &j);
		c[i].token = token_read(input, &j);
		i++;
	}
	c[i].cmd = NULL;
	return ;
}

int	command_counter(char *input)
{
	int	i;
	int	command_count;

	command_count = 1;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '<' || input[i] == '>' || input[i] == '|')
				&& space_check(input + i, 0) == 0 && input[i + 1])
		{
			command_count++;
		}
		if ((input[i] == '<' && input[i + 1] == '<' && input[i + 2] &&
				space_check(input + i, 1) == 0) || (input[i] == '>' &&
					input[i + 2] && input[i + 1] == '>' &&
						space_check(input + i, 1) == 0))
		{
			command_count++;
			i++;
		}
		i++;
	}
	return (command_count);
}