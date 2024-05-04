/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:55:22 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/04 22:56:04 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*truncate_input(char *input)
{
	t_count	c;
	int		ind;
	char	*tmp;

	c.i = 0;
	ind = 0;
	c.quote_count = 0;
	while (input[c.i] && ind == 0)
	{
		if (input[c.i] == 34 || input[c.i] == 39)
			c.quote_count++;
		if ((input[c.i] == '<' || input[c.i] == '>') && c.quote_count % 2 != 1)
			ind = 1;
		c.i++;
	}
	if (!input[c.i])
		return (input);
	tmp = input;
	input = malloc(sizeof(char) * (c.i));
	ft_strlcpy(input, tmp, c.i);
	free(tmp);
	return (input);
}

int	cmd_parser(t_cmd *cmd, char *input, int pipe)
{
	int	ind;
	int	j;

	j = 0;
	while (input[j] == ' ' || input[j] == '	')
		j++;
	ind = own_check(input);
	cmd->cmd = cmd_read(input, &j);
	cmd->input = ft_strdup(input);
	cmd->arg = arg_read(input, ind, &j);
	if (pipe == 1)
		cmd->token = 1;
	else
		cmd->token = 0;
	redirection_read(cmd, input, &j);
	cmd->input = truncate_input(cmd->input);
	return (0);
}

t_cmd	*cmd_creator(char **splitted)
{
	int		i;
	t_cmd	*cmd;
	int		pipe;

	i = 0;
	pipe = 0;
	while (splitted[i])
		i++;
	if (i > 1)
		pipe = 1;
	cmd = malloc(sizeof(t_cmd) * (i + 1));
	i = 0;
	while (splitted[i])
	{
		cmd_parser(&cmd[i], splitted[i], pipe);
		i++;
	}
	cmd[i].cmd = NULL;
	free_splitted(splitted);
	return (cmd);
}

t_cmd	*parser(char *input, char **env, int ex)
{
	char	**splitted;
	t_cmd	*cmd;

	cmd = NULL;
	splitted = NULL;
	if (!input[0])
		return (NULL);
	splitted = lexer(input);
	if (!splitted)
		return (NULL);
	cmd = cmd_creator(splitted);
	if (cmd[0].cmd)
		expansion(cmd, env, ex);
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
	{
		if (cmd[i].cmd)
			free(cmd[i].cmd);
		if (cmd[i].arg)
			free(cmd[i].arg);
		if (cmd[i].input)
			free(cmd[i].input);
		if (cmd[i].ifile)
			free(cmd[i].ifile);
		if (cmd[i].ofile)
			free(cmd[i].ofile);
		cmd[i].ored = 0;
		cmd[i].ired = 0;
		i++;
	}
	free(cmd);
}
