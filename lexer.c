/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:25:03 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/19 16:27:47 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_lexer(t_cmd cmd)
{
	if (cmd.option)
		printf("env: '%s': No such file or directory", cmd.option);
	if (cmd.arg)
		printf("env: '%s': No such file or directory", cmd.arg);
}

int	own_check(char *cmd)
{
	int	i;

	i = 0;
	if (ft_strncmp(cmd, "env", 3) == 0)
		return(1);
	if (ft_strncmp(cmd, "unset", 5) == 0)
		return(2);
	if (ft_strncmp(cmd, "cd", 2) == 0)
		return(3);
    if (ft_strncmp(cmd, "export", 6) == 0)
		return(4);
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return(5);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return(6);
	else
		return (-1);

}

char	*paste_var(int index, char *arg, char *var, t_list *env)
{
	char 	*result;
	int		i;
	
	i = 0;
	result = malloc(sizeof(char) * (ft_strlen(arg) - ft_strlen(var)
			+ ft_strlen(ft_getenv(env, var))));
	while(i < index)
	{
		result[i] = arg[i];
		i++;
	}
	index += ft_strlcpy(result + i, ft_getenv(env, var),
				ft_strlen(ft_getenv(env, var)) + 1);
	i += ft_strlen(var) + 1;
	while(arg[i])
	{
		result[index] = arg[i];
		index++;
		i++;
	}
	result[index] = 0;
	return (result);
}

char	*exchange(char *arg, int index, t_list *env)
{
	char	*var;
	char	*result;
	int		i;

	i = 0;
	var = ft_substr(arg, index + 1, substr_len(arg + index + 1));
	if (!ft_getenv(env, var))
	{
		free(var);
		free(arg);
		return (NULL);
	}
	result = paste_var(index, arg, var, env);
	free(var);
	free(arg);
	return (result);
}

void	expander(t_cmd *cmd, t_list *env)
{
	int		i;
	int		quote_count;
	char	*arg;

	i = 0;
	quote_count = 0;
	while (cmd->arg && cmd->arg[i] != '\0')
	{
		if (cmd->arg[i] == 39)
			quote_count++;
		if (cmd->arg[i] == '$' && quote_count % 2 != 1 && cmd->arg[i + 1]
			&& ft_isprint(cmd->arg[i + 1]) == 1 && cmd->arg[i + 1] != '?')
		{
			arg = cmd->arg;
			cmd->arg = exchange(arg, i, env);
		}
		i++;
	}
}

int	own_lexer(t_cmd *cmd, int ind, t_list *env)
{
	if (ind == 1 && (cmd->option || cmd->arg))
	{
		env_lexer(*cmd);
		return (-1);
	}
	if (ind == 2 && cmd->option)
	{
		printf("unset: bad option: %s", cmd->option);
		return (-1);
	}
	if (ind == 4 && cmd->option)
	{
		printf("export: bad option: %s", cmd->option);
		return (-1);
	}
	if (ind == 5 && cmd->option && ft_strncmp(cmd->option, "-n", 2) != 0)
	{
		printf("echo: bad option: %s", cmd->option);
		return (-1);	
	}
	if (ind != 4 && (ind != 5 && !cmd->arg))
		expander(cmd, env);
	return (0);
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

char	*delete_quotation(char *input)
{
	int		i;
	char	*result;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == 34 || input[i] == 39)
			count++;
		i++;
	}
	result = malloc(sizeof(char) * (ft_strlen(input) - count + 1));
	i = 0;
	while (input[i + j])
	{
		while (input[i + j] && (input[i + j] == 34 || input[i + j] == 39))
			j++;
		result[i] = input[i + j];
		if (input[i + j])
			i++;
	}
	result[i] = 0;
	free(input);
	return (result);
}

int	remove_quotation(t_cmd *cmd)
{
	if (unclosed_quotes(cmd->cmd) != -1)
		return (-1);
	if (cmd->input)
		cmd->input = delete_quotation(cmd->input);
	if (cmd->cmd)
		cmd->cmd = delete_quotation(cmd->cmd);
	if (cmd->arg)		
		cmd->arg = delete_quotation(cmd->arg);
	return (0);
}

int	command_lexer(t_cmd *c, t_list *env)
{
	int		i;
	int		ind;

	i = 0;
	while (c[i].cmd)
	{
		ind = own_check(c[i].cmd);
		if (ind > 0)
		{
			if (own_lexer(&c[i], ind, env) == -1)
				return (-1);
		}
		else
			expander(&c[i], env);
		if (remove_quotation(&c[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
