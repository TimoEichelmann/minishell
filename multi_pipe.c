/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:38:54 by snegi             #+#    #+#             */
/*   Updated: 2024/04/24 16:04:09 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	operate_pipe(t_basic *basic, int i, int **fd , t_shell *shell)
{
	int	j;

	j = 0;
	printf("%d.......%d\n",shell->file, shell->ofile);
	if (i > 0 && shell->file == 0)
		dup2(fd[i - 1][0], 0);
	else
		close(fd[i-1][0]);
	if (i < basic->pipe_num && shell->ofile == 0)
		dup2(fd[i][1], 1);
	else
		close(fd[i][1]);
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
	//int		cmd_id;

	if (token_check(&cmd[i], &shell) == -1)
 		printf("No such file exist \n");
	else
	{
		operate_pipe(basic, i, fd, &shell);
		// cmd_id = own_check(cmd[i].cmd); 
		// if (cmd_id == 4 || cmd_id == 2 || cmd_id == 3) 
		// 	printf("");
		// if (cmd_id == 1 || cmd_id == 5 || cmd_id == 6)
		// 	exit (our_functions(cmd, basic));
		// if (cmd_id == -1)
		// {
		// 	shell.command_arg = ft_split(cmd[i].input, ' ');
		// 	shell.path = getenv("PATH");
		// 	shell.command_path = ft_split(shell.path, ':');
		// 	shell.command = get_command(shell.command_path, shell.command_arg[0]);
		// 	if (shell.command == NULL)
		// 		printf("No Such Command.\n");
		// 	else if (execve(shell.command, shell.command_arg, basic->env) == -1)
		// 		perror("execve failed.");
		// 	free_memory(&shell);
		//}
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
			execution(i, fd, cmd, basic);
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
