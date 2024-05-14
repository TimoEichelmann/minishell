/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supporting_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:41:18 by snegi             #+#    #+#             */
/*   Updated: 2024/05/14 14:03:25 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	printf("%s", str);
	exit(8);
}

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
	i = 0;
	if (shell->command_arg)
	{
		while (shell->command_arg[i])
			free(shell->command_arg[i++]);
		free(shell->command_arg);
	}
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

void	ft_exit(t_basic *basic, t_cmd *cmd)
{
	int	number;
	int	out;

	number = 6;
	if (!cmd)
	{
		del_env(basic->env);
		exit (0);
	}
	out = check_numerical(cmd->arg);
	if (out == -1 || cmd->code .
	ifile || cmd->ofile)
		printf("numeric argument required\n");
	if (out == 0)
		number = ft_atoi(cmd->arg);
	if (basic->pipe_num <= 0)
		free_cmd(cmd);
	del_env(basic->env);
	exit (number);
}

int	our_functions(t_cmd *cmd, t_basic *basic)
{
	if ((ft_strncmp(cmd->cmd, "echo", 4) == 0) && (basic->pipe_num > 0
			|| !(ft_getenv(basic->env, "PATH"))))
		return (echo(cmd));
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		return (ft_unset(basic->env, cmd->arg));
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		if (ft_export(&basic->env, cmd->arg) == -1)
			return (7);
	}
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		ft_pwd(basic);
	else if (!ft_getenv(basic->env, "PATH"))
		return (-5);
	else if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ft_env(basic->env);
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
		return (maintain_cd(cmd->input + 2, basic->env) == 1);
	else if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
		ft_exit(basic, cmd);
	else
		return (-1);
	return (0);
}
