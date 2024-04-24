/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:22:53 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/24 16:17:22 by teichelm         ###   ########.fr       */
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

t_cmd	*parser(char *input, char **env, int ex_status)
{
	t_cmd	*cmd;
	int			cmd_count;
	int			unclosed;
	int			status;

	unclosed = unclosed_quotes(input);
	if (unclosed != -1)
		return (NULL);
	cmd_count = command_counter(input);
	if (!cmd_count)
		return (NULL);
	cmd = malloc(sizeof(t_cmd) * (cmd_count + 1));
	command_parser(input, &cmd, cmd_count);
	status = command_lexer(cmd, env, ex_status);
	if (status == -1)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

int	readers(t_cmd *cmd, int ind)
{
	
	c->input = input_read(input, &j);
	if (!c->input)
		return ;
	c[i]->cmd = cmd_read(input, &j);
	if (ft_strncmp(c[i]->cmd, "echo", 5) == 0)
		ind = 1;
	c[i]->option = opt_read(input, &j, ind);
	ind = 0;
	c[i]->arg = arg_read(input, &j);
	c[i]->token = token_read(input, &j, &c[i]->file);
}

void	command_parser(char	*input, t_cmd **cmd, int cmd_count)
{
	int			i;
	int			j;
	int			ind;
	t_cmd		*c;

	j = 0;
	i  = 0;
	ind = 0;
	c = *c;
	while (i < cmd_count)
	{
		readers(&c[i], ind)
		i++;
	}
	c[i].cmd = NULL;
	return ;
}

int	command_counter(char *input)
{
	int	i;
	int	command_count;
	int	quotation_count;
	
	command_count = 1;
	i = 0;
	while (input[i] && ft_isalnum(input[i]) == 0)
		i++;
	if (!input[i])
		return (0);
	quotation_count = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			quotation_count++;
		if (input[i] == '|' && quotation_count % 2 != 1 && input[i + 1])
		{
			command_count++;
		}
		i++;
	}
	return (command_count);
}
