/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:17:59 by snegi             #+#    #+#             */
/*   Updated: 2024/04/25 10:18:01 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_command(char **path, char *command)
{
	char	*temp;
	char	*cmd;

	while (*path)
	{
		temp = ft_strjoin(*path, "/");
		cmd = ft_strjoin(temp, command);
		free(temp);
		if (access(cmd, F_OK) == 0)
			return (cmd);
		free (cmd);
		path++;
	}
	return (NULL);
}

int	check_path(char *str, t_shell *shell)
{
	int	i;
	char	*str1;

	i = 0;
	str1 = ft_strrchr(str, '/');
	if (str1 == NULL)
		return (0);
	else
	{
		shell->command_arg = ft_split(str1, ' ');
		shell->command_path = ft_split(str, ' ');
		shell->command = shell->command_path[0];
		if (access(shell->command, F_OK) != 0)
			shell->command = NULL;
	}
	return (1);
}

void	shell_command(t_cmd *cmd, t_basic *basic)
{
	t_shell	shell;

	basic->pipe_num = 0;
	if (token_check(cmd, &shell) == -1)
		print_error("No such file exist \n");
	if (!(check_path(cmd->input, &shell)))
	{
		shell.command_arg = ft_split(cmd->input, ' ');
		shell.path = getenv("PATH");
		shell.command_path = ft_split(shell.path, ':');
		shell.command = get_command(shell.command_path, shell.command_arg[0]);
	}
	if (shell.command == NULL)
		print_error("No Such Command.\n");
	else if (execve(shell.command, shell.command_arg, basic->env) == -1)
		perror("execv failed.");
	free_memory(&shell);
}

void	single_exec(t_cmd *cmd, t_basic *basic)
{
	int	pid;

	basic->exit_status = our_functions(cmd, basic);
	if (basic->exit_status == 6)
		exit (5);
	if (basic->exit_status == -1)
	{
		pid = fork();
		if (pid == 0)
		{
			shell_command(cmd, basic);
			exit(1);
		}
		else
			waitpid(pid, &(basic->exit_status), 0);
	}
}
