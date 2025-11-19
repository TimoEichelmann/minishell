/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:59:25 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//start = index of cut place len == char * len u want to cut
char	*cut_str(char *str, int start, int len)
{
	char	*new;
	int		i;

	i = start;
	if (!str)
		return (NULL);
	if (ft_strlen(str) - len + 1 <= 1)
	{
		free(str);
		return (NULL);
	}
	new = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	ft_strlcpy(new, str, start);
	while (i < len)
		i++;
	ft_strlcpy(new + start, str + start + len, ft_strlen(str + start + len));
	free(str);
	return (new);
}

//fill=str to pace|start=index of position to pace in|len=charachters to cpy
char	*paste_str(char *str, char *fill, int start, int len)
{
	char	*new;

	if (!fill)
		return (str);
	if (!str)
		return (ft_strdup(fill));
	new = malloc(sizeof(char) * (ft_strlen(str) + len + 1));
	ft_strlcpy(new, str, start);
	ft_strlcpy(new + start, fill, len);
	ft_strlcpy(new + ft_strlen(new), str + start, ft_strlen(str));
	free(str);
	return (new);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i].end)
	{
		j = 0;
		while (cmd[i].cmd && cmd[i].cmd[j])
		{
			free(cmd[i].cmd[j]);
			j++;
		}
		free(cmd[i].cmd);
		j = 0;
		while (cmd[i].red && cmd[i].red[j])
		{
			free(cmd[i].red[j]);
			j++;
		}
		free(cmd[i].red);
		i++;
	}
	free(cmd);
}

char	not_space(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	return (str[i]);
}
