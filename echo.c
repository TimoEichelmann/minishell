/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:21:00 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/24 15:24:21 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmd *cmd, t_basic *basic)
{
	int	i;
	int	ind;

	i = 0;
	ind = 0;
	if (!cmd->arg)
	{
		write(1, "\n", 1);
		return (0);
	}
	if (cmd->option && strncmp(cmd->option, "-n", 2) == 0)
		ind = 1;
	while (cmd->arg[i])
	{
		if (cmd->arg[i] == '$' && cmd->arg[i + 1] == '?')
		{
			i += 2;
			printf("%d\n", basic->exit_status);
		}
		write(1, &cmd->arg[i], 1);
		i++;
	}
	if (ind == 0)
		printf("\n");
	return (0);
}
