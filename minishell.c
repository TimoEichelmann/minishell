/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:17 by snegi             #+#    #+#             */
/*   Updated: 2024/04/26 02:28:57 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	print_error(char *str)
{
	printf("%s",str);
	exit(0);
}

void	ft_pwd(t_basic *basic)
{
	char **ev;

	ev = basic->env;
	while (*ev && ev[0] != NULL)
	{
		if (strncmp(*ev, "PWD=", 4) == 0)
		{
			 printf("%s\n", *ev + 4);
			 return;
		}
		ev++;
	}
	printf("PWD not found\n");
}

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
    free(shell->command);
	if (shell->file > 0)
		close(shell->file);
}

void sigint_handler(int signal) 
{
	signal--;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

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

int    our_functions(t_cmd *cmd, t_basic *basic)
{
	if (ft_strncmp(cmd->cmd, "env", 3) == 0)
		ft_env(basic->env);
    else if (ft_strncmp(cmd->cmd, "unset", 5) == 0)
		ft_unset(basic->env, cmd->arg);
	else if (ft_strncmp(cmd->cmd, "export", 6) == 0)
		ft_export(&basic->env, cmd->arg);
	else if (ft_strncmp(cmd->cmd, "cd", 2) == 0)
       basic->exit_status = maintain_cd(basic->input + 2, basic->env);
	else if (ft_strncmp(cmd->cmd, "exit", 5) == 0)
		ft_exit(basic->env);
	else if (ft_strncmp(cmd->cmd, "echo", 4) == 0)
		echo(cmd, basic);
	else if (ft_strncmp(cmd->cmd, "pwd", 3) == 0)
		ft_pwd(basic);
	else
		return (-1);
	return (0);
}

void	shell_command(t_cmd *cmd, t_basic *basic)
{
	t_shell shell;

	shell.file = 0;
	basic->pipe_num = 0;
	if (token_check(cmd, &shell) == -1)
		print_error("No such file exist \n");
	shell.command_arg = ft_split(cmd->input, ' ');
   	shell.path = getenv("PATH");
    shell.command_path = ft_split(shell.path, ':');
    shell.command = get_command(shell.command_path, shell.command_arg[0]);
    if(shell.command == NULL)
        print_error("No Such Command.\n");
    else if (execve(shell.command, shell.command_arg, basic->env) == -1)
        perror("execv failed.");
    free_memory(&shell);
}

void	single_exec(t_cmd *cmd, t_basic *basic)
 {
	
 	int	pid;

    basic->exit_status = our_functions(cmd, basic);
    if(basic->exit_status == 6)
		exit(5);
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

void	ft_exit(char **env)
{
	del_env(env);
	exit (1);
}

int	count_pipes(t_cmd *cmd)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (cmd[i].cmd)
	{
		if (cmd[i].token == 1)
		i++;
	}
	return (result);
}

void init(t_basic *basic,char  **env)
{
    t_cmd *cmd;

	env++;
	cmd = parser(basic->input/*,  env, */ /* basic->exit_status */);
    if (cmd == NULL)
	{
    	return ;
	}
	basic->pipe_num = count_pipes(cmd);
    if (basic->pipe_num < 1)
	 	single_exec(cmd, basic);
	else
	  	main_exec(basic, cmd);
	free_cmd(cmd);
}

int main(int ac, char **av, char **ev)
{
    t_basic    basic;

    if(ac == 1 && !av[1])
    {
        basic.exit_status = 0;
		basic.env = init_env(ev);
        signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
        while (1)
        {
			basic.input = NULL;
            basic.input = readline("$> ");
			if (!basic.input)
				ft_exit(basic.env);
            add_history(basic.input);
            init(&basic, basic.env);
		}
    	del_env(basic.env);
	}
    return 0;
}
