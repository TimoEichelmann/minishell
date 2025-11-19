/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:38:54 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	shell.command_arg = NULL;
	shell.command_path = NULL;
	token_check(cmd, &shell);
	operate_pipe(basic, i, fd, &shell);
	if (cmd == NULL)
		exit(1);
	if (our_functions(cmd, basic) == -1)
	{
		get_shelldata(&shell, basic, cmd);
		if (execve(shell.command, shell.command_arg, basic->env) == -1)
		{
			perror("execve failed");
			free_memory(&shell);
			exit(EXIT_FAILURE);
		}
		free_memory(&shell);
	}
}

int	process_fork(t_basic *basic, t_cmd *cmd, int **fd, pid_t *pids)
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
		{
			execution(i, fd, &cmd[i], basic);
			exit(0);
		}
		pids[i] = pid;
		i++;
	}
	return (0);
}

void	wait_process(t_basic *basic, int **fd, pid_t *pids)
{
	int	i;
	int	status;

	i = 0;
	while (i < basic->pipe_num)
	{
		close(fd[i][0]);
		close(fd[i++][1]);
	}
	i = 0;
	while (i <= basic->pipe_num)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		basic->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status)) 
		basic->exit_status = 128 + WTERMSIG(status);
	i = 0;
	while (i < basic->pipe_num)
		free (fd[i++]);
	free(fd);
	free(pids);
}

int	main_exec(t_basic *basic, t_cmd *cmd )
{
	int		**fd;
	int		i;
	pid_t	*pids;

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
	pids = malloc(sizeof(pid_t) * (basic->pipe_num + 1));
	if (process_fork(basic, cmd, fd, pids) == -2)
		return (-2);
	wait_process(basic, fd, pids);
	return (0);
}
