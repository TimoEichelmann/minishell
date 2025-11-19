/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supporting_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:41:18 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_memory(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->command_path)
	{
		while (shell->command_path[i])
			free(shell->command_path[i++]);
		free(shell->command_path);
	}
	if (shell->command)
		free(shell->command);
	if (shell->file > 0)
		close(shell->file);
	if (shell->ofile > 0)
		close(shell->ofile);
}

int	check_numerical(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (-2);
	while (arg && arg[i])
	{
		if (ft_isdigit(arg[i]) == 0 && arg[i] != '-'
			&& arg[i] != '+' && arg[i] != ' ')
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_argnum(char **cmd)
{
	int	i;
	int	res;

	i = 1;
	res = 1;
	while (cmd && cmd[i] != NULL)
		i++;
	if (i == 2)
		res = ft_atoi(cmd[1]);
	else if (i > 2)
	{
		i = 2;
		while (cmd && cmd[i++] != NULL)
		{
			res = check_numerical(cmd[i]);
			if (i == -1)
			{
				printf("numeric argument required\n");
				return (2);
			}
		}
		printf("too many arguments\n");
		res = 1;
	}
	return (res);
}

void	ft_exit(t_basic *basic, t_cmd *cmd)
{
	int	number;
	int	i;

	number = 2;
	printf("exit\n");
	if (!cmd || !cmd->cmd || !cmd->cmd[1])
	{
		del_env(basic->env);
		exit (0);
	}
	if (cmd->cmd[1])
	{
		i = check_numerical(cmd->cmd[1]);
		if (i == -1)
			printf("numeric argument required\n");
		if (i == 0)
			number = check_argnum(cmd->cmd);
	}
	if (basic->pipe_num <= 0)
		free_cmd(cmd);
	del_env(basic->env);
	basic->exit_status = number;
	exit (number);
}

int	our_functions(t_cmd *cmd, t_basic *basic)
{
	if (!cmd)
		return (0);
	if (!cmd->cmd)
		return (-1);
	else if (basic->pipe_num > 0 && cmd->cmd[0] && 
		ft_strncmp(cmd->cmd[0], "echo\0", 5) == 0)
		return (echo(cmd));
	else if (cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "unset\0", 6) == 0)
		return (ft_unset(basic->env, cmd->cmd));
	else if (cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "export\0", 7) == 0)
		return (ft_export(&basic->env, cmd->cmd, NULL));
	else if (cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "env\0", 4) == 0)
		return (ft_env(basic->env, cmd));
	else if (cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
		ft_exit(basic, cmd);
	else if (cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "pwd\0", 4) == 0)
		ft_pwd(basic);
	else if (cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "cd\0", 3) == 0)
		return (maintain_cd(cmd->cmd, basic->env) == 1);
	else
		return (-1);
	return (0);
}
