/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supporting_fun.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:41:18 by snegi             #+#    #+#             */
/*   Updated: 2024/05/03 13:35:46 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *str)
{
	printf("%s", str);
	strerror(5);
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

void	ft_exit(char **env)
{
	del_env(env);
	exit (0);
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
	if (!ft_getenv(basic->env, "PATH"))
		return (-5);
	if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ft_env(basic->env);
	else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		ft_unset(basic->env, cmd->arg);
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
	{
		if (ft_export(&basic->env, cmd->arg) == -1)
			exit(7);
	}
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
	{
		if (maintain_cd(basic->input + 2, basic->env) == 1)
			exit(6);
	}
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		ft_exit(basic->env);
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		echo(cmd);
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		ft_pwd(basic);
	else
		return (-1);
	return (0);
}
