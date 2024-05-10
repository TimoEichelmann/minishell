/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:44:55 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/10 16:55:20 by teichelm         ###   ########.fr       */
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

char	**split_input(char *input)
{
	int		size;
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	size = splitted_size(input);
	result = malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		result[i] = splitted_string(input, &j);
		if (input[j + 1])
			j += 1;
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**lexer(char *input)
{
	int		cmd_num;
	char	**splitted;
	int		i;

	i = 0;
	cmd_num = count_cmds(input);
	splitted = split_input(input);
	while (splitted[i])
		i++;
	if (cmd_num != 1 && cmd_num != i - 1)
	{
		print_check(-2, splitted);
		return (NULL);
	}
	if (checks(splitted) == -1)
		return (NULL);
	return (splitted);
}

char	*cmd_read(char *input, int *j)
{
	char	*result;
	int		i;

	i = 0;
	result = word(input + *j);
	while (result[i] == ' ' || result[i] == '	')
		i++;
	*j += ft_strlen(result) + i;
	return (result);
}

int	true_env(char *env)
{
	int	i;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	if (!env[i] || (env[i] == '=' && !env[i + 1]))
		return (-1);
	return (0);
}

void	expansion(t_cmd *cmd, char **env, int ex)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
	{
		cmd[i].arg = expander(cmd[i].arg, env, ex);
		cmd[i].input = expander(cmd[i].input, env, ex);
		cmd[i].ifile = expander(cmd[i].ifile, env, ex);
		cmd[i].ofile = expander(cmd[i].ofile, env, ex);
		remove_quotation(&cmd[i]);
		i++;
	}
}
