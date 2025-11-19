/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:21:00 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	echo(t_cmd *cmd)
{
	t_count	c;
	int		ind;

	c.i = 1;
	c.j = 0;
	ind = 0;
	if (!cmd->cmd)
	{
		printf("\n");
		return (0);
	}
	if (cmd->cmd[1] && strncmp(cmd->cmd[1], "-n\0", 3) == 0)
		ind = 1;
	while (cmd->cmd[c.i])
	{
		printf("%s", cmd->cmd[c.i]);
		c.i++;
	}
	if (ind == 0)
		printf("\n");
	return (0);
}
