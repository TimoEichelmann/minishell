/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:17 by snegi             #+#    #+#             */
/*   Updated: 2024/04/19 16:39:45 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void    free_memory(t_shell *shell)
{
    int	i;

	i = 0;
    if(shell->command_path)
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
}

void sigint_handler() 
{
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

static char	*get_command(char **path, char *command)
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

// void	execution(t_shell *shell, char **ev)
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == 0)
// 	{
//         shell->command = get_command(shell->command_path, shell->command_arg[0]);
//         if(shell->command == NULL)
//             printf("No Such Command.\n");
//         else if (execve(shell->command, shell->command_arg, ev) == -1)
//                 perror("execv failed.");
//         free(shell->command);
//         free_memory(shell);
//         exit(1);
// 	}
// 	else
// 		wait(0);
// }




void	ft_exit(t_list *env)
{
	del_env(env);
	printf("h");
	return ;
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd[i].cmd)
	{
		if (cmd[i].input)
			free(cmd[i].input);
		if (cmd[i].cmd)
			free(cmd[i].cmd);
		if (cmd[i].option)
			free(cmd[i].option);
		if (cmd[i].arg)
			free(cmd[i].arg);
		if (cmd[i].token)
			free(cmd[i].token);
		i++;
	}
	free(cmd);
}

int	count_pipes(t_cmd *cmd)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (cmd[i].cmd)
	{
		if (cmd[i].token && ft_strncmp(cmd[i].token, "|", 1) == 0)
		{
			printf("hello");
			result++;		
		}
		i++;
	}
	return (result);
}

void execution(t_shell *shell, char **ev, int i, int fd[][2], int no) {
    if (i > 0)
        dup2(fd[i - 1][0], 0);
    if (i < no)
        dup2(fd[i][1], 1);
    
    for (int j = 0; j < no; j++) {
        if (i == j)
            close(fd[i][0]);
        else if (i ==  j + 1)
            close(fd[j][1]);

        if (i != j && i != j + 1)
        {
            close(fd[j][0]);
            close(fd[j][1]);
        }
    }

    shell->command = get_command(shell->command_path, shell->command_arg[0]);
	// check for own functions
    if (shell->command == NULL)
        printf("No Such Command.\n");
    else if (execve(shell->command, shell->command_arg, ev) == -1)
        perror("execve failed.");
    free(shell->command);
}

int	main_exec(int no, char **ev, char **av/* t_cmd *cmd */, t_list *env)
{
    t_shell shell;
    int fd[no][2];
    int pid[no + 3];
    int i;

    for(i = 0; i< no ; i++)
    {
        if(pipe(fd[i]) < 0)
            return -1;
    }
    for (i = 0; i <= no; i++)
    {
        pid[i] = fork();
        if(pid[i] < 0)
            return -2;
         if (pid[i] == 0)
         { 
            shell.command_arg = ft_split(av[i + 1], ' ');
            shell.path = ft_getenv(env, "PATH");
            shell.command_path = ft_split(shell.path, ':');
            execution(&shell, ev, i, fd, no);
         }
    }
    for (i = 0; i < no; i++)
	{
        close(fd[i][0]);
        close(fd[i][1]);
    }
    for (i = 0; i<= no; i++)
        waitpid(pid[i], NULL, 0);
    return 0;
}

int main(int ac, char **av, char **ev)
{
    // t_shell shell;
    char *input;
    char *promt;
	char	**env;
	t_cmd	*cmd;
	// int		pipe_num;

	env = NULL;
    if(ac == 1 && !av[1])
    {
		env = init_env(ev);
        promt = ">$ ";
        signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
        while (1)
        {
            input = readline(promt);
			if (!input || ft_strncmp(input, "exit", 5) == 0)
			{
				ft_exit(env);
				exit(5);
			}
            add_history(input);
			cmd = parser(input, env);
			int i = 0;
			if (cmd)
			{
			while (cmd[i].cmd)
			{
				printf("input :%s cmd :%s opt :%s arg :%s tok :%s\n", cmd[i].input, cmd[i].cmd, cmd[i].option, cmd[i].arg, cmd[i].token);
				i++;
			}
			}
			// pipe_num = count_pipes(cmd);
			// if (pipe_num <= 1)
			// 	single_exec(cmd, env)
			// else
			// 	main_exec(pipe_num, ev, av, env);
			free_cmd(cmd);
		}
    	del_env(env);
	}
    return 0;
}


			// if (ft_strncmp(input, "env", 3) == 0)
			// 	ft_env(env);
			// if (ft_strncmp(input, "unset", 5) == 0)
			// 	ft_unset(&env, input + 5);
            // else if (ft_strncmp(input, "cd", 2) == 0)
            //     promt = maintain_cd(input + 2, promt);
            // else if (ft_strncmp(input, "export", 6) == 0)
            //     ft_export(&env, input + 6);
			// else if (ft_strncmp(input, "echo", 4) == 0)
			// 	echo(input + 5, env);
			// else
            // {
            //     shell.command_arg = ft_split(input, ' ');
            //     shell.path = getenv("PATH");
            //     shell.command_path = ft_split(shell.path, ':');
            //     execution(&shell,ev);
            //     free_memory(&shell);
            // }
