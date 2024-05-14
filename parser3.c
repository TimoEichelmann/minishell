/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:44:55 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/14 12:12:03 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	splitted_size(char *input)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	c.count = 1;
	while (input[c.i])
	{
		if (input[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (input[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if ((input[c.i] == '|' && c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1)
			|| !input[c.i])
			c.count++;
		c.i++;
	}
	return (c.count);
}

char	*splitted_string(char *input, int *j)
{
	t_count	c;

	c.i = *j;
	c.j = *j;
	c.qcount34 = 0;
	c.qcount39 = 0;
	c.count = 1;
	while (input[c.i])
	{
		if (input[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (input[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if ((input[c.i] == '|' && c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1)
			|| !input[c.i + 1])
			return (ft_substr(input, c.j, c.i - c.j + 1));
		c.i++;
		*j += 1;
	}
	return (NULL);
}

void	outfile_read(t_cmd *cmd, int oneed, char *input)
{
	if (input[oneed + 1] == '>')
		cmd->ored = 2;
	else
		cmd->ored = 1;
	while (input[oneed] == ' ' || input[oneed] == '>'
		|| input[oneed] == 34 || input[oneed] == 39)
		oneed++;
	cmd->ofile = word(input + oneed - 1);
	return ;
}

void	infile_read(t_cmd *cmd, int ineed, char *input)
{
	if (input[ineed + 1] == '<')
		cmd->ired = 2;
	else
		cmd->ired = 1;
	while (input[ineed] == ' ' || input[ineed] == '<'
		|| input[ineed] == 34 || input[ineed] == 39)
		ineed++;
	cmd->ifile = word(input + ineed - 1);
	return ;
}

void	redirection_read(t_cmd *cmd, char *input)
{
	int	need;
	int	oneed;
	int	ineed;

	ineed = 0;
	oneed = 0;
	need = redirection_need(input, &ineed, &oneed);
	cmd->ired = 0;
	cmd->ored = 0;
	cmd->ifile = NULL;
	cmd->ofile = NULL;
	if (need == 0)
		return ;
	if (oneed > 0)
		outfile_read(cmd, oneed, input);
	if (ineed > 0)
		infile_read(cmd, ineed, input);
	cmd->arg = remove_redirection(cmd->arg);
	cmd->input = remove_redirection(cmd->input);
}
