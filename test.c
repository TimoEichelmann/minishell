/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:42:42 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/10 17:32:08 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*cmd_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	')
		i++;
	result = ft_substr(input, *j, i);
	*j = *j + i;
	return (result);
}

char	*opt_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	if (input[*j] != '-')
		return (NULL);
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	')
		i++;
	result = ft_substr(input, *j, i);
	*j += i;
	return (result);
}

int	space_check(char *input, int ind)
{
	int	i;

	i = 0;
	if (ind == 0)
	{
		if (input[i + 1] && input[i - 1] && (input[i + 1] == ' '
			|| input[i + 1] == '	') && (input[i - 1] == ' '
			|| input[i - 1] == '	'))
			return (0);
		if (!input[i + 1] && (input[i - 1] == ' ' || input[i - 1] == '	'))
			return (0);
		return (1);
	}
	if (input[i + 2] && (input[i - 1] == ' ' || input[i - 1] == '	')
		&& (input[i + 2] == ' ' || input[i + 2] == '	'))
		return (0);
	if (!input[i + 2] && (input[i - 1] == '	' || input[i + 2] == ' '))
		return (0);
	return (1);
}

int	is_token(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if ((c[i] == '<' || c[i] == '>' || c[i] == '|') &&
			space_check(c + i, 0) == 0)
			return (i);
		if ((c[i] == '<' && c[i + 1] == '<' &&
			space_check(c + i, 1) == 0) || (c[i] == '>' &&
				c[i + 1] == '>' && space_check(c + i, 1) == 0))
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
	printf("i : %d %c\n", i, input[i + *j]);
	if (i == 0)
		return (NULL);
	result = ft_substr(input, *j, i - 1);
	*j += i;
	return (result);
}



char	*token_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	if (!input[*j])
		return (NULL);
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	')
		i++;
	// if (input[i + *j] == ' ' || input[i + *j] == '	')
	// 	i--;
	result = ft_substr(input, *j, i);
	*j += i;
	return (result);
}

//remove spaces at end
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

t_cmd	*parser(char *input)
{
	t_cmd	*cmd;
	int			cmd_count;

	cmd_count = command_counter(input);
	cmd = malloc(sizeof(t_cmd) * (cmd_count + 1));
	command_parser(input, &cmd, cmd_count);
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
		i++;
	while (cmd[i].cmd)
	{
		if (cmd[i].cmd)
			free(cmd[i].cmd);
		if (cmd[i].option)
			free(cmd[i].option);
		if (cmd[i].arg)
			free(cmd[i].arg);
		if (cmd[i].token)
			free(cmd[i].token);
		i--;
	}
	free(cmd);
}

int main(int argc, char **argv)
{
	char *input = argv[1];
	t_cmd *r;
	argc--;
	
	int	i = 0;
	r = parser(input);
	while (r[i].cmd)
	{
		printf("c %s o %s a %s t %s\n", r[i].cmd, r[i].option, r[i].arg, r[i].token);
		free(r[i].cmd);
		free(r[i].option);
		free(r[i].arg);
		free(r[i].token);
		i++;
	}
	free_cmd(r);
}