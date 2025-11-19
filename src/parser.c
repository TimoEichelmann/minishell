/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:29:12 by timo              #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	parser_loop(char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		str[i] = remover(str[i]);
		if (!str[i] && str[i + 1])
		{
			str[i] = malloc(sizeof(char) * 1);
			str[i][0] = 0;
		}
		i++;
	}
}

void	parser(int ind, char *cmd, t_cmd *res)
{
	char	*tmp;

	if (!cmd || !cmd[0] || (cmd[0] == ' ' && !cmd[1]))
	{
		res->end = 1;
		res->cmd = NULL;
		return ;
	}
	parser_loop(res->red);
	tmp = cmd;
	res->cmd = split_cmds(cmd, ' ');
	if (ft_strncmp(res->cmd[0], "echo\0", 5) == 0 && ind == 1)
	{
		res->cmd[1] = cut_str(res->cmd[1], 0, 1);
		res->cmd[1] = cut_str(res->cmd[1], ft_strlen(res->cmd[1]) - 1, 1);
	}
	free(tmp);
	res->end = 1;
	parser_loop(res->cmd);
}

int	echo_check(char **splitted)
{
	char	*sp;

	sp = *splitted;
	if (sp && ft_strncmp(sp, "echo ", 5) == 0
		&& not_space(sp + 5) != 34 && not_space(sp + 5) != 39)
	{
		sp = paste_str(sp, "\"", 5, 1);
		sp = paste_str(sp, "\"", ft_strlen(sp), 1);
		*splitted = sp;
		return (1);
	}
	*splitted = sp;
	return (0);
}

t_cmd	*creator(char *input, char **env, int exit_status)
{
	char	**sp;
	t_cmd	*cmd;
	int		i;

	i = 0;
	input = free_strtrim(input);
	input = expander(input, env, exit_status);
	if (!input)
		return (NULL);
	sp = split_cmds(input, '|');
	cmd = malloc(sizeof(t_cmd) * (split_size(input, NULL, NULL, '|') + 1));
	while (sp[i])
	{
		sp[i] = free_strtrim(sp[i]);
		cmd[i].red = NULL;
		cmd[i].red = redirect(&sp[i], cmd[i].red);
		if (sp[i])
			sp[i] = free_strtrim(sp[i]);
		parser(echo_check(&sp[i]), sp[i], &cmd[i]);
		i++;
	}
	free(input);
	free(sp);
	cmd[i].end = 0;
	return (cmd);
}
