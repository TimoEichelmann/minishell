/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:17:59 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	int		i;
	char	*str1;

	i = 0;
	str1 = ft_strrchr(str, '/');
	if (str1 == NULL)
		return (0);
	else
	{
		shell->command_path = ft_split(str, ' ');
		shell->command = shell->command_arg[0];
		if (access(shell->command, F_OK) != 0)
			shell->command = NULL;
	}
	return (1);
}

void	get_shelldata(t_shell *shell, t_basic *basic, t_cmd *cmd)
{
	char	*input;

	shell->command_arg = cmd->cmd;
	if (!(check_path(cmd->cmd[0], shell)) && ft_getenv(basic->env, "PATH"))
	{
		shell->path = ft_getenv(basic->env, "PATH");
		shell->command_path = ft_split(shell->path, ':');
		shell->command = get_command(shell->command_path, 
				shell->command_arg[0]);
	}
	if (shell->command == NULL)
		print_shellerror(": No Such Command.\n", cmd->cmd[0], shell, 127);
	input = getcwd(NULL, 0);
	if (chdir(shell->command) == 0)
	{
		free(input);
		print_shellerror(":Is a directory\n", shell->command, shell, 126);
	}
	chdir(input);
	free(input);
}

void	shell_command(t_cmd *cmd, t_basic *basic)
{
	t_shell	shell;

	shell.command = NULL;
	shell.command_arg = NULL;
	shell.command_path = NULL;
	basic->pipe_num = 0;
	token_check(cmd, &shell);
	if (!cmd->cmd || cmd->cmd[0] == NULL)
		exit(0);
	if (cmd->cmd[0] && ft_strncmp(cmd->cmd[0], "echo\0", 5) == 0)
		exit (echo(cmd));
	get_shelldata(&shell, basic, cmd);
	if (execve(shell.command, shell.command_arg, basic->env) == -1)
	{
		perror("execve failed");
		free_memory(&shell);
		exit(EXIT_FAILURE);
	}
	exit(0);
}

void	single_exec(t_cmd *cmd, t_basic *basic)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		shell_command(cmd, basic);
	}
	else
	{
		signal(SIGINT, handle_exec_sig);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			basic->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			basic->exit_status = 128 + WTERMSIG(status);
	}
}
