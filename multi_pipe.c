/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:38:54 by snegi             #+#    #+#             */
/*   Updated: 2024/05/14 12:30:44 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	operate_pipe(t_basic *basic, int i, int **fd, t_shell *shell)
{
	int	j;

	j = 0;
	if (i > 0 && shell->file == 0)
		dup2(fd[i - 1][0], 0);
	if (i < basic->pipe_num && shell->ofile == 0)
		dup2(fd[i][1], 1);
	while (j < basic->pipe_num)
	{
		if (i == j)
			close(fd[i][0]);
		else if (i == j + 1)
			close(fd[j][1]);
		if (i != j && i != j + 1)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		j++;
	}
}

void	execution(int i, int **fd, t_cmd *cmd, t_basic *basic)
{
	t_shell	shell;

	shell.command = NULL;
	if (token_check(cmd, &shell) == 2) 
		exit(0);
	operate_pipe(basic, i, fd, &shell);
	if (cmd == NULL)
		exit(1);
	if (our_functions(cmd, basic) == -1)
	{
		get_shelldata(&shell, basic, cmd);
		if (shell.command == NULL)
			print_error("No Such Command.\n");
		else if (execve(shell.command, shell.command_arg, basic->env) == -1)
			print_error("execv failed.:No Such file/directory.\n");
		free_memory(&shell);
	}
	exit (0);
}

int	process_fork(t_basic *basic, t_cmd *cmd, int **fd)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (i <= basic->pipe_num)
	{
		pid = fork();
		if (pid < 0)
			return (-2);
		if (pid == 0)
			execution(i, fd, &cmd[i], basic);
		i++;
	}
	return (0);
}

void	wait_process(t_basic *basic, int **fd)
{
	int	i;

	i = 0;
	while (i < basic->pipe_num)
	{
		close(fd[i][0]);
		close(fd[i++][1]);
	}
	i = 0;
	while (i <= basic->pipe_num)
	{
		waitpid(-1, &basic->exit_status, 0);
		i++;
	}
	if (basic->exit_status == 13)
		basic->exit_status = 0;
	i = 0;
	while (i < basic->pipe_num)
		free (fd[i++]);
	free(fd);
}

int	main_exec(t_basic *basic, t_cmd *cmd )
{
	int	**fd;
	int	i;

	i = 0;
	fd = malloc(sizeof(int *) * basic->pipe_num);
	if (fd == NULL)
		return (-1);
	while (i < basic->pipe_num)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (fd[i++] == NULL)
			return (-1);
	}
	i = 0;
	while (i < basic->pipe_num)
	{
		if (pipe(fd[i++]) < 0)
			return (-1);
	}
	if (process_fork(basic, cmd, fd) == -2)
		return (-2);
	wait_process(basic, fd);
	return (0);
}
