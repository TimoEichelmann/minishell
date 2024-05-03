/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:46:09 by snegi             #+#    #+#             */
/*   Updated: 2024/05/03 15:18:16 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count(char **str)
{
	int	i;

	i = 0;
	while (*str && str[i] != NULL)
		i++;
	return (i);
}

int	count_pipe(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str == '|')
			i++;
		str++;
	}
	return (i);
}

t_cmd	*store_cmd(char **input, int no)
{
	t_cmd	*cmd;
	char	**temp;
	int		i;

	cmd = NULL;
	cmd = malloc(sizeof(t_cmd) * (no + 1));
	while (*input && *input != NULL)
	{
		temp = ft_split(*input, ' ');
		cmd->input = ft_strdup(input[0]);
		i = 0;
		while (*temp  && temp[i] != NULL)
			free(temp[i++]);
		free(temp);
		input++;
		cmd++;
	}
	cmd = NULL;
	return (cmd);
}

int	check_error(char **input)
{
	int	i;

	i = 0;
	while (*input && *input != NULL)
	{
		input++;
	}
	return (0);
}

t_cmd   *create_cmd(t_basic *basic)
{
	t_cmd *cmd;
	char **input;
	int pipe_no;

	cmd = NULL;
	pipe_no = count_pipe(basic->input);
	input = ft_split(basic->input , '|');
	basic->pipe_num = count(input) - 1;
	if (basic->pipe_num != pipe_no)
		return (cmd);
	cmd = store_cmd(input, pipe_no + 1);
	//if (check_error(input) == 1)
		//return (NULL);
	return (cmd);
}