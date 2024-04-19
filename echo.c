/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:21:00 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/19 16:33:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmd *cmd, t_list *env, t_basic basic)
{
	int	i;


	i = 0;
	ind = 0;
	if (cmd->arg)
		return (0);
	if (cmd->option && strncmp(cmd->option, "-n", 2) == 0)
		ind = 1;
	while (cmd->arg[i])
	{
		if (cmd->arg[i] == '$' && cmd->arg[i + 1] == '?')
			printf("%d\n", basic.exit_status);
		printf("%c", cmd->arg[i]);
		i++;
	}
	if (ind == 0)
		printf("\n");
	return (0);
}
