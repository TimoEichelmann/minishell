/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:17 by snegi             #+#    #+#             */
/*   Updated: 2024/04/15 17:37:16 by teichelm         ###   ########.fr       */
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

void	execution(t_shell *shell, char **ev)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
        shell->command = get_command(shell->command_path, shell->command_arg[0]);
        if(shell->command == NULL)
            printf("No Such Command.\n");
        else if (execve(shell->command, shell->command_arg, ev) == -1)
                perror("execv failed.");
        free(shell->command);
        free_memory(shell);
        exit(1);
	}
	else
		wait(0);
}


// change value if variable already exists


void	ft_exit(t_list *env)
{
	del_env(env);
	printf("h");
	return ;
}

// int right_input(char *input)
// {
//     int single;
//     int doub;

//     single = 0;
//     doub = 0;
//     while(*input  && *input != '\0')
//     {
//         if (*input == 34)
//             doub++;
//         else if(*input == 39)
//             single++;
//         input++;
//     }
//     if (doub % 2 == 0 && single % 2 == 0)
//         return (1);
//     else
//         return (0);
// }

// int	check_input(char *input)
// {
		
// }



//remove spaces at end




void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
		i++;
	while (cmd[i].cmd)
	{
		if (cmd[i].cmd)
			free(cmd[i].cmd);
		if (cmd[i].option)
			free(cmd[i].option);
		if (cmd[i].arg)
			free(cmd[i].arg);
		if (cmd[i].token)
			free(cmd[i].token);
		i--;
	}
	free(cmd);
}

int main(int ac, char **av, char **ev)
{
    // t_shell shell;
    char *input;
    char *promt;
	t_list	*env;
	t_cmd	*cmd;

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
            add_history(input);
			cmd = parser(input, env);
			// if (!input || ft_strncmp(input, "exit", 5) == 0)
			// {
			// 	ft_exit(env);
			// 	exit(5);
			// }
			int i = 0;
			while(cmd[i].cmd)
			{
				printf("main cmd: '%s' opt: '%s' arg: '%s' tok: '%s'\n", cmd->cmd, cmd->option, cmd->arg, cmd->token);
				i++;
			}
			
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
