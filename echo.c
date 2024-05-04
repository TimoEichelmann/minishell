/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:21:00 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/04 22:56:14 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(t_cmd *cmd)
{
	int	i;
	int	ind;

	i = 0;
	ind = 0;
	if (!cmd->arg)
	{
		printf("\n");
		return (0);
	}
	if (strncmp(cmd->arg, "-n", 2) == 0)
	{
		i = 2;
		while (cmd->arg[i] == ' ' || cmd->arg[i] == '	')
			i++;
		ind = 1;
	}
	while (cmd->arg[i])
	{
		printf("%c", cmd->arg[i]);
		i++;
	}
	if (ind == 0)
		printf("\n");
	return (0);
}
