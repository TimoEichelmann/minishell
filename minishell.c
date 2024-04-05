/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:17 by snegi             #+#    #+#             */
/*   Updated: 2024/04/05 15:49:41 by teichelm         ###   ########.fr       */
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

int	substr_len(char *substr)
{
	int	i;

	i = 0;
	while (substr[i] && substr[i] != ' '
		&& substr[i] != 34 && substr[i] != 39 && substr[i] != '$')
		i++;
	return (i);
}

void	new_env(t_list **env, char *input)
{
	int	i;
	int	j;
	t_list	*new;
	char	*var;

	i = 0;
	j = 0;
	new = malloc(sizeof(t_list));
	// var = (char *)new->c;
	new->c = malloc(sizeof(char) * ft_strlen(input) + 1);
	var = new->c;
	ft_strlcpy(var, input, ft_strlen(input) + 1);
	ft_lstadd_back(env, new);
}


void	ft_unset(t_list **env, char *name)
{
	t_list	*p;
	t_list	*temp;

	while (*name == ' ')
		name++;
	p = *env;
	while (p->next && ft_strncmp((char *)p->next->c, name, ft_strlen(name)) != 0)
		p = p->next;
	if (p->next)
	{
		temp = p->next;
		p->next = p->next->next;
		free(temp->c);
		free(temp);
	}
	else
	{
		temp = p->next;
		free(temp->c);
		free(temp);
		p->next = NULL;
	}
}

void    ft_export(t_list **env, char *input)
{
    char *name;
    int i;
	char	*val;

	i = 0;
    while (*input && *input == ' ')
        input++;
    if (*input)
    {
        while (input[i] && input[i] != '=')
            i++;
		if (!input[i + 1] || (input[i] == '=' && !input[i + 1]))
		{
			printf("Usage: export NAME=value\n");
			return ;
		}
		name = ft_substr(input, 0, i);
		val = ft_getenv(*env, name);
		if (!val)
			new_env(env, input);
		else
		{
			ft_unset(env, name);
			new_env(env, input);
			// change_env(env, name, input);
		}
		free(name);
    }
    else
        printf("Invalid argument format for export\n");
}

int	print_env(t_list *env, char *input, int i)
{
	int	len;
	char	*var;
	char	*val;

	var = ft_substr(input + i, 1, substr_len(input + i + 1));
	val = ft_getenv(env, var);
	len = ft_strlen(var) + 1;
	printf("%s", val);
	free(var);
	return (len);
}

void	echo(char *input, t_list *env)
{
	int	i;
	int	ind;


	i = 0;
	ind = 0;
	if (strncmp(input, "-n", 2) == 0)
	{	
		input += 3;
		ind = 1;
	}
	while (input[i])
	{
		if (input[i] == '$')
			i += print_env(env, input, i);
		if (input[i] != 34 && input[i] != 39 && input[i] && input[i] != '$')
		{
			printf("%c", input[i]);
			i++;
		}
		if (input[i] == 34 || input[i] == 39)
			i++;
	}
	if (ind == 0)
		printf("\n");
}

t_list	*init_env(char **ev)
{
	int	i;
	t_list	*env;
	t_list	*head;

	i = 0;
	head = NULL;
	while (ev[i])
	{
		env = malloc(sizeof(t_list));
		env->c = ft_strdup(ev[i]);
		ft_lstadd_back(&head, env);
		i++;
	}
	return (head);
}

char	*ft_getenv(t_list *env, char *name)
{
	int		i;
	char	*c;
	int		ind; 

	i = 0;
	ind = 0;
	while (name[i] == ' ')
		name++;
	while (env && ind == 0)
	{
		c = (char *)env->c;
		if (ft_strncmp(c, name + i, ft_strlen(name)) == 0)
			ind = 1;
		else
			env = env->next;
	}
	if (!env)
		return (NULL);
	i = 0;
	while (c[i] != '=')
		i++;
	return (c + i + 1);
	//must not be modified!!!!
}
// change value if variable already exists
void	del_env(t_list *env)
{
	while (env)
	{
		free(env->c);
		env = env->next;
	}
	free(env);
}

void	ft_env(t_list *env)
{
	char *c;

	while (env)
	{
		c = env->c;
		printf("%s\n", c);
		env = env->next;
	}
}

void	ft_exit(t_list *env)
{
	del_env(env);
	printf("h");
	return ;
}

int main(int ac, char **av, char **ev)
{
    // t_shell shell;
    char *input;
    char *promt;
	t_list	*env;

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
			if (!input || ft_strncmp(input, "exit", 5) == 0)
			{
				ft_exit(env);
				exit(5);
			}
			if (ft_strncmp(input, "env", 3) == 0)
				ft_env(env);
			if (ft_strncmp(input, "unset", 5) == 0)
				ft_unset(&env, input + 5);
			if (ft_strncmp(input, "getenv", 6) == 0)
				printf("%s\n", ft_getenv(env, input + 6));
            // else if (ft_strncmp(input, "cd", 2) == 0)
            //     promt = maintain_cd(input + 2, promt);
            else if (ft_strncmp(input, "export", 6) == 0)
                ft_export(&env, input + 6);
            // else if (ft_strncmp(input, "unset", 5) == 0)
            //     remove_env(ev, input + 5);
			else if (ft_strncmp(input, "echo", 4) == 0)
				echo(input + 5, env);
            // else
            // {
            //     shell.command_arg = ft_split(input, ' ');
            //     shell.path = getenv("PATH");
            //     shell.command_path = ft_split(shell.path, ':');
            //     execution(&shell,ev);
            //     free_memory(&shell);
            // }
    	}
    del_env(env);
	}
    return 0;
}
