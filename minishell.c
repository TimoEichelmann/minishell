/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:17 by snegi             #+#    #+#             */
/*   Updated: 2024/04/10 17:32:33 by teichelm         ###   ########.fr       */
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
		if (input[i] == '$' && check_single_quotes(input) == 0)
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

int right_input(char *input)
{
    int single;
    int doub;

    single = 0;
    doub = 0;
    while(*input  && *input != '\0')
    {
        if (*input == 34)
            doub++;
        else if(*input == 39)
            single++;
        input++;
    }
    if (doub % 2 == 0 && single % 2 == 0)
        return (1);
    else
        return (0);
}

int	check_input(char *input)
{
		
}

int	iterate_quotes(char *input, int ind, int i)
{
	int	quote_count;
	int	quote_check;

	quote_count = 0;
	quote_check = 0;
	while (input[i])
	{
		if (ind == 1 && input[i] == 34 || ind == 2 && input[i] == 39)
			quote_count++;
		i++;
	}
	i = 0;
	if (quote_count % 2 == 1)
	{
		while (quote_check != quote_count)
		{
			if (ind == 1 && input[i] == 34 || ind == 2 && input[i] == 39)
				quote_check++;
			i++;
		}
		return (i - 1);
	}
	return (-1);
}

int	unclosed_quotes(char *input)
{
	int	squote;
	int	dquote;
	int	i;

	i = 0;
	squote = iterate_quotes(input, 2, i);
	dquote = iterate_quotes(input, 1, i);
	if (dquote == -1 && squote >= 0)
		return (squote);
	if (squote == -1 && dquote >= 0)
		return (dquote);
	if (dquote > squote && squote > 0)
		return (squote);
	if (squote > dquote && dquote > 0)
		return (dquote);
	if (squote == dquote)
		return (squote);
	return (0);
}

char	*cmd_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	')
		i++;
	result = ft_substr(input, *j, i);
	*j = *j + i;
	return (result);
}

char	*opt_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	if (input[*j] != '-')
		return (NULL);
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	')
		i++;
	result = ft_substr(input, *j, i);
	*j += i;
	return (result);
}

int	space_check(char *input, int ind)
{
	int	i;

	i = 0;
	if (ind == 0)
	{
		if (input[i + 1] && input[i - 1] && (input[i + 1] == ' '
			|| input[i + 1] == '	') && (input[i - 1] == ' '
			|| input[i - 1] == '	'))
			return (0);
		if (!input[i + 1] && (input[i - 1] == ' ' || input[i - 1] == '	'))
			return (0);
		return (1);
	}
	if (input[i + 2] && (input[i - 1] == ' ' || input[i - 1] == '	')
		&& (input[i + 2] == ' ' || input[i + 2] == '	'))
		return (0);
	if (!input[i + 2] && (input[i - 1] == '	' || input[i + 2] == ' '))
		return (0);
	return (1);
}

int	is_token(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if ((c[i] == '<' || c[i] == '>' || c[i] == '|') &&
			space_check(c + i, 0) == 0)
			return (i);
		if ((c[i] == '<' && c[i + 1] == '<' &&
			space_check(c + i, 1) == 0) || (c[i] == '>' &&
				c[i + 1] == '>' && space_check(c + i, 1) == 0))
			return (i);
		i++;
	}
	if (!c[i])
		return (i);
	return (0);
}

char	*arg_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	if (!input[*j])
		return (NULL);
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	if (!input[*j])
		return (NULL);
	while (i < is_token(input + *j))
		i++;
	printf("i : %d %c\n", i, input[i + *j]);
	if (i == 0)
		return (NULL);
	result = ft_substr(input, *j, i - 1);
	*j += i;
	return (result);
}



char	*token_read(char *input, int *j)
{
	int		i;
	char	*result;

	i = 0;
	while (input[*j] && (input[*j] == ' ' || input[*j] == '	'))
		*j += 1;
	if (!input[*j])
		return (NULL);
	while (input[i + *j] && input[i + *j] != ' ' && input[i + *j] != '	')
		i++;
	// if (input[i + *j] == ' ' || input[i + *j] == '	')
	// 	i--;
	result = ft_substr(input, *j, i);
	*j += i;
	return (result);
}

//remove spaces at end
void	command_parser(char	*input, t_cmd **cmd, int cmd_count)
{
	t_cmd	*c;
	int			i;
	int			j;

	j = 0;
	i  = 0;
	c = *cmd;
	while (i < cmd_count)
	{
		c[i].cmd = cmd_read(input, &j);
		c[i].option = opt_read(input, &j);
		c[i].arg = arg_read(input, &j);
		c[i].token = token_read(input, &j);
		i++;
	}
	c[i].cmd = NULL;
	return ;
}

int	command_counter(char *input)
{
	int	i;
	int	command_count;

	command_count = 1;
	i = 0;
	while (input[i])
	{
		if ((input[i] == '<' || input[i] == '>' || input[i] == '|')
				&& space_check(input + i, 0) == 0 && input[i + 1])
		{
			command_count++;
		}
		if ((input[i] == '<' && input[i + 1] == '<' && input[i + 2] &&
				space_check(input + i, 1) == 0) || (input[i] == '>' &&
					input[i + 2] && input[i + 1] == '>' &&
						space_check(input + i, 1) == 0))
		{
			command_count++;
			i++;
		}
		i++;
	}
	return (command_count);
}

t_cmd	*parser(char *input)
{
	t_cmd	*cmd;
	int			cmd_count;

	cmd_count = command_counter(input);
	cmd = malloc(sizeof(t_cmd) * (cmd_count + 1));
	command_parser(input, &cmd, cmd_count);
	return (cmd);
}
//command -opt -arg | command2 -opt2 -arg2

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
			cmd = parser(input);
			if (!input || ft_strncmp(input, "exit", 5) == 0)
			{
				ft_exit(env);
				exit(5);
			}
			splitted = parser(input);
			check_input(splitted);
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
