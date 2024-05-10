/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:44:41 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/10 19:15:44 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *input, int i)
{
	t_count	c;

	c.qcount34 = 0;
	c.qcount39 = 0;
	c.i = 0;
	if (input[i] != '|')
		return (-1);
	while (c.i < i)
	{
		if (input[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (input[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		c.i++;
	}
	if (c.qcount34 % 2 == 1 || c.qcount39 % 2 == 1)
		return (-1);
	return (0);
}

char	*arg_read(char *input, int ind, int *j)
{
	char	*result;
	int		i;

	i = 0;
	result = NULL;
	
	if (ind < 0)
		return (NULL);
	while (input[*j] == ' ')
		*j += 1;
	while (input[i + *j] && check_pipe(input, i + *j) != 0)
		i++;
	if (i > 0)
		result = ft_substr(input, *j, i);
	return (result);
}

char	*ft_return(char *str, int i)
{
	if (i == 0)
		return (NULL);
	return (str);
}

char	*delete_redirection(char *str, int i)
{
	int		j;
	char	*len;
	int		p;

	j = 0;
	while (str[i + j] == ' ' || str[i + j] == '<' || str[i + j] == '>')
		j++;
	len = word(str + i + j);
	p = ft_strlen(len) + j;
	while (str[i + p] == ' ')
		p++;
	free(len);
	if (i > 0 && str[i - 1] != ' ')
	{
		str[i] = ' ';
		p--;
		i++;
	}
	while (str[i + p])
	{
		str[i] = str[p + i];
		i++;
	}
	str[i] = 0;
	return (ft_return(str, i));
}

char	*remove_redirection(char *str)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (str && str[c.i])
	{
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if ((str[c.i] == '<' || str[c.i] == '>')
			&& c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1)
		{
			delete_redirection(str, c.i);
			c.i--;
		}
		c.i++;
	}
	return (str);
}

int	redirection_need(char *in, int *ineed, int *oneed)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (in[c.i])
	{
		if (in[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (in[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (in[c.i] == '<' && c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1)
			*ineed = c.i;
		if (in[c.i] == '>' && c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1)
			*oneed = c.i;
		if ((in[c.i] == '<' || in[c.i] == '>') && c.qcount34 % 2 != 1
			&& c.qcount39 % 2 != 1 && (in[c.i + 1] == '<'
				|| in[c.i + 1] == '>'))
			c.i++;
		c.i++;
	}
	if (*oneed > 0 || *ineed > 0)
		return (1);
	return (0);
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
	// printf("%d %d %d\n", need, ineed, oneed);
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
