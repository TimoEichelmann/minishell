/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:44:41 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/03 14:45:36 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*arg_read(char *input, int ind, int *j)
{
	char	*result;
	char	*pot;
	char	*tmp;
	
	result = NULL;
	if (ind < 0)
		return (NULL);
	pot = word(input + *j);
	while (check_true_arg(pot) == 0)
	{
		tmp = result;
		result = ft_strjoin(result, " \0");
		free(tmp);
		tmp = result;
		result = ft_strjoin(result, pot);
		free(tmp);
		*j += ft_strlen(pot) + 1;
		free(pot);
		pot = word(input + *j);
	}
	if (pot)
		free(pot);
	return (result);
}

int	redirection_need(char *input)
{
	t_count	c;
	int	need;

	c.i = 0;
	need = 0;
	c.quote_count = 0;
	while (input[c.i])
	{
		if (input[c.i] == 34 || input[c.i] == 39)
			c.quote_count++;
		if ((input[c.i] == '<' && input[c.i + 1] == '<') || input[c.i] == '<')
		{
			c.i++;
			need += 5;
		}
		if ((input[c.i] == '>' && input[c.i + 1] == '>') || input[c.i] == '>')
		{
			c.i++;
			need -= 2;
		}
		c.i++;
	}
	return (need);
}

void	input_need(t_cmd *cmd, int need, char *input, int *j)
{
	char	*result;
	int		i;

	i = *j;
	if (need == -2)
	{
		cmd->ifile = NULL;
		cmd->ired = 0;
		return ;
	}
	while (input[i] != '<')
		i += 1;
	if (input[i + 1] == '<')
	{
		cmd->ired = 1;
		i++;
	}
	i += 1;
	if (input[i] == '<')
		i += 1;
	result = word(input + i);
	cmd->ifile = result;
	cmd->ired += 1;
}

void	output_need(t_cmd *cmd, int need, char *input, int *j)
{
	char	*result;
	int		i;

	i = *j;
	if (need == 5)
	{
		cmd->ofile = NULL;
		cmd->ored = 0;
		return ;
	}
	while (input[i] != '>')
		i += 1;
	i++;
	if (input[i] == '>')
	{
		cmd->ored = 1;
		i += 1;
	}
	result = word(input + i);
	cmd->ofile = result;
	cmd->ored += 1;
}

void	redirection_read(t_cmd *cmd, char *input, int *j)
{
	int	need;

	need = redirection_need(input);
	if (need == 0)
	{
		cmd->ired = 0;
		cmd->ored = 0;
		cmd->ifile = NULL;
		cmd->ofile = NULL;
		return ;
	}
	output_need(cmd, need, input, j);
	input_need(cmd, need, input, j);
}
