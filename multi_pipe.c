/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:38:54 by snegi             #+#    #+#             */
/*   Updated: 2024/04/24 16:06:05 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    operate_pipe(t_basic *basic,int i, int fd[][2])
{
    int j;

    j = 0;
    if (i > 0)
        dup2(fd[i - 1][0], 0);
    if (i < basic->pipe_num)
        dup2(fd[i][1], 1);
    while (j < basic->pipe_num) 
    {
        if (i == j)
            close(fd[i][0]);
        else if (i ==  j + 1)
            close(fd[j][1]);            shell.command_arg = ft_split(cmd[i].input, ' ');
        if (i != j && i != j + 1)
        {
            close(fd[j][0]);
            close(fd[j][1]);
        }
        j++;
    }
}

void    execution(int i, int fd[][2], t_cmd *cmd, t_basic *basic)
{
    t_shell shell;

    operate_pipe(basic,i,fd);
    // if (token_check(cmd, &shell) == -1)
	// 	printf("No such file exist \n");
    // else
    // {
        basic->exit_status = own_check(cmd[i].cmd);
		printf("%d", basic->exit_status);
        if(basic->exit_status == 4 || basic->exit_status == 2 || basic->exit_status ==3) 
        printf("");
        if (basic->exit_status == 1 || basic->exit_status == 5 || basic->exit_status == 6)
        exit ( our_functions(cmd, basic));
        if(basic->exit_status == -1)
        {
            shell.command_arg = ft_split(cmd[i].input, ' ');
            shell.path = getenv("PATH");
            shell.command_path = ft_split(shell.path, ':');
            shell.command = get_command(shell.command_path, shell.command_arg[0]);
            if (shell.command == NULL)
                printf("No Such Command.\n");
            else if (execve(shell.command, shell.command_arg, basic->env) == -1)
                perror("execve failed.");
            free_memory(&shell);
        }
    //}
    exit(0);
}

int    process_fork(t_basic *basic, t_cmd *cmd, int fd[][2], int pid[])
{
    int i;

    i = 0;
    while( i <= basic->pipe_num)
    {
        pid[i] = fork();
        if(pid[i] < 0)
            return -2;
         if (pid[i] == 0)
           execution(i, fd, cmd, basic);
         i++;
    }
    return (0);
}

int	main_exec(t_basic *basic, t_cmd *cmd )
{
    int fd[basic->pipe_num][2];
    int pid[basic->pipe_num];
    int i;

    i = 0;
    while (i< basic->pipe_num)
    {
        if(pipe(fd[i++]) < 0)
            return -1;
    }
    if (process_fork(basic,cmd, fd, pid) == -2)
        return -2;
    i = 0;
    while (i < basic->pipe_num)
    {
        close(fd[i][0]);
        close(fd[i][1]);
        i++;
    }
    i = 0;
    while(i<= basic->pipe_num)
        waitpid(pid[i++], &(basic->exit_status), 0);
    return 0;
}
