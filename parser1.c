/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:55:22 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/28 13:26:30 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*delete_pipe(char	*input)
// {
// 	t_count	c;

// 	c.i = 0;
// 	c.qcount34 = 0;
// 	c.qcount39 = 0;
// 	while (input[c.i])
// 	{
// 		if (input[c.i] == 34 && c.qcount39 % 2 != 1)
// 			c.qcount34++;
// 		if (input[c.i] == 39 && c.qcount34 % 2 != 1)
// 			c.qcount39++;
// 		if (input[c.i] == '|' && c.qcount39 % 2 != 1 && c.qcount34 % 2 != 1)
// 		{
// 			input[c.i] = 0;
// 			return (input);
// 		}
// 		c.i++;
// 	}
// 	return (input);
// }

// int	cmd_parser(t_cmd *cmd, char *input, int pipe)
// {
// 	int	ind;
// 	int	j;

// 	j = 0;
// 	while (input[j] == ' ' || input[j] == '	')
// 		j++;
// 	ind = own_check(input);
// 	cmd->cmd = cmd_read(input, &j);
// 	cmd->input = delete_pipe(ft_strdup(input));
// 	cmd->arg = arg_read(input, ind, &j);
// 	if (pipe == 1)
// 		cmd->token = 1;
// 	else
// 		cmd->token = 0;
// 	cmd->ired = 0;
// 	cmd->ored = 0;
// 	redirection_read(cmd, input);
// 	return (0);
// // }

// t_cmd	*cmd_creator(char **splitted)
// {
// 	int		i;
// 	t_cmd	*cmd;
// 	int		pipe;

// 	i = 0;
// 	pipe = 0;
// 	while (splitted[i])
// 		i++;
// 	if (i > 1)
// 		pipe = 1;
// 	cmd = malloc(sizeof(t_cmd) * (i + 1));
// 	i = 0;
// 	while (splitted[i])
// 	{
// 		cmd_parser(&cmd[i], splitted[i], pipe);
// 		i++;
// 	}
// 	cmd[i].cmd = NULL;
// 	free_splitted(splitted);
// 	return (cmd);
// }

// t_cmd	*parser(char *input, char **env, int ex)
// {
// 	char	**splitted;
// 	t_cmd	*cmd;

// 	cmd = NULL;
// 	splitted = NULL;
// 	if (!input[0])
// 		return (NULL);
// 	splitted = lexer(input);
// 	if (!splitted)
// 		return (NULL);
// 	cmd = cmd_creator(splitted);
// 	if (cmd[0].cmd)
// 		expansion(cmd, env, ex);
// 	return (cmd);
// }

// void	free_cmd(t_cmd *cmd)
// {
// 	int	i;

// 	i = 0;
// 	while (cmd[i].cmd)
// 	{
// 		if (cmd[i].cmd)
// 			free(cmd[i].cmd);
// 		if (cmd[i].arg)
// 			free(cmd[i].arg);
// 		if (cmd[i].input)
// 			free(cmd[i].input);
// 		if (cmd[i].ifile)
// 			free(cmd[i].ifile);
// 		if (cmd[i].ofile)
// 			free(cmd[i].ofile);
// 		cmd[i].ored = 0;
// 		cmd[i].ired = 0;
// 		i++;
// 	}
// 	free(cmd);
// }
