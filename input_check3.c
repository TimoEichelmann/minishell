/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:40:54 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/14 12:05:58 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word(char *p)
{
	t_count	c;

	c.i = 0;
	c.j = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (p[c.j] && (p[c.j] == ' ' || p[c.j] == '<' || p[c.j] == '>'))
		c.j++;
	while (p[c.i + c.j])
	{
		if (p[c.i + c.j] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (p[c.i + c.j] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1 && (p[c.i + c.j] == ' '
				|| p[c.i + c.j] == '	' || p[c.i + c.j] == '|'
				|| p[c.i + c.j] == '<' || p[c.i + c.j] == '>'))
			return (ft_substr(p, c.j, c.i));
		c.i++;
	}
	if (c.i + c.j == 0)
		return (NULL);
	return (ft_substr(p, c.j, c.i));
}

char	*cmd_word_check(char *p)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = word(p);
	while (cmd[i])
	{
		if (cmd[i] == ' ' || cmd[i] == '	')
			return (cmd);
		i++;
	}
	free(cmd);
	return (NULL);
}

int	check_words(char **splitted)
{
	int		i;
	char	*cmd;

	i = 0;
	while (splitted[i])
	{
		cmd = cmd_word_check(splitted[i]);
		if (cmd != NULL)
		{
			printf("no such command : %s\n", cmd);
			free(cmd);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	checks(char **splitted)
{
	int	ind1;
	int	ind2;
	int	ind4;

	ind1 = check_quotation(splitted);
	if (ind1 < 0)
		return (print_check(ind1, splitted));
	ind2 = check_empty(splitted);
	if (ind2 < 0)
		return (print_check(ind2, splitted));
	ind4 = check_words(splitted);
	if (ind4 < 0)
		return (print_check(ind4, splitted));
	return (0);
}

int	own_check(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == '	' || cmd[i] == ' ' || cmd[i] == 39 || cmd[i] == 34)
		i++;
	if (ft_strncmp(cmd + i, "env", 3) == 0)
		return (1);
	if (ft_strncmp(cmd + i, "unset", 5) == 0)
		return (2);
	if (ft_strncmp(cmd + i, "cd", 2) == 0)
		return (3);
	if (ft_strncmp(cmd + i, "export", 6) == 0)
		return (4);
	if (ft_strncmp(cmd + i, "echo", 4) == 0)
		return (5);
	if (ft_strncmp(cmd + i, "exit", 4) == 0)
		return (6);
	if (ft_strncmp(cmd + i, "pwd", 3) == 0)
		return (7);
	else
		return (-1);
}
