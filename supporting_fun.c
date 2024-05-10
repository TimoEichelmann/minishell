/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supporting_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:41:18 by snegi             #+#    #+#             */
/*   Updated: 2024/05/10 15:09:14 by teichelm         ###   ########.fr       */
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
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == 0 && arg[i] != '-' && arg[i] != '+' && arg[i] != ' ')
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

void	ft_exit(char **env, t_cmd *cmd)
{
	int number;

	number = 6;
	if (!cmd)
	{
		del_env(env);
		exit (0);
	}
	if (check_numerical(cmd->arg) != 0)
		printf("numeric argument required\n");
	else
		number = ft_atoi(cmd->arg);
	free_cmd(cmd);
	del_env(env);
	exit (number);
}

void	ft_pwd(t_basic *basic)
{
	char	**ev;

	ev = basic->env;
	while (*ev && ev[0] != NULL)
	{
		if (strncmp(*ev, "PWD=", 4) == 0)
		{
			printf("%s\n", *ev + 4);
			return ;
		}
		ev++;
	}
	printf("PWD not found\n");
}

int	our_functions(t_cmd *cmd, t_basic *basic)
{
	if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		return(echo(cmd));
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
		ft_exit(basic->env, cmd);
	else
		return (-1);
	return (0);
}
