/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:25:03 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/24 16:00:00 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_lexer(t_cmd cmd)
{
	if (cmd.option)
	{
		printf("env: '%s': No such file or directory\n", cmd.option);
		return (-1);
	}
	if (cmd.arg)
	{
		printf("env: '%s': No such file or directory\n", cmd.arg);
		return (-1);
	}
	return (0);
}

int	export_lexer(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '=')
		i++;
	if (arg[i + 1] == ' ' || arg[i + 1] == '	'
		|| arg[i - 1] == ' ' || arg[i - 1] == '	')
		return (1);
	return (0);
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

char	*paste_var(int index, char *arg, char *var, char **env)
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

char	*exchange(char *arg, int index, char **env)
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

void	ft_paste(char *result, char *str, char *num)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && (str[i] != '$' && str[i + 1] != '?'))
	{
		result[i] = str[i];
		i++;
	}
	while (num[j])
	{
		result[i + j] = num[j];
		j++;	
	}
	i += j;
	while (str[i - j + 2])
	{
		result[i] = str[i - j + 2];
		i++;
	}
	result[i] = 0;
}

char *paste_ex_status(char *str, int ex_status)
{
	char	*result;
	char	*num;
	
	num = ft_itoa(ex_status);
	result = malloc(sizeof(char) * (ft_strlen(str) - 1 + ft_strlen(num)));
	ft_paste(result, str, num);
	free(str);
	free(num);
	return (result);
}

char	*expander(char *str, char **env, int ex_status)
{
	int		i;
	int		quote_count;
	char	*arg;

	i = 0;
	quote_count = 0;
	while (str && str[i] != '\0')
	{
		if (str[i] == 39)
			quote_count++;
		if (str[i] == '$' && str[i + 1] == '?')
			str = paste_ex_status(str, ex_status);
		if (str[i] == '$' && quote_count % 2 != 1 && str[i + 1]
			&& ft_isprint(str[i + 1]) == 1 && str[i + 1] != '?')
		{
			arg = str;
			str = exchange(arg, i, env);
		}
		i++;
	}
	return (str);
}

int	print_lexerror(char *function, char *error)
{
	if (error)
		printf("%s: bad option: %s\n", function, error);
	else
		printf("%s: bad argument\n", function);
	return (-1);
}

int	own_lexer(t_cmd *cmd, int ind, char **env, int ex_status)
{
	if (ind == 1 && (cmd->option || cmd->arg) && env_lexer(*cmd) == -1)
		return (-1);
	if (ind == 2 && (!cmd->arg || cmd->arg[0] == '-'))
		return (print_lexerror(cmd->cmd, NULL));
	if (ind == 4)
	{
		if (cmd->option)
			return (print_lexerror(cmd->cmd, cmd->option));
		if (!cmd->arg || export_lexer(cmd->arg) == 1)
		{
			printf("export: wrong variable declaration\n");
			return (-1);
		}
	}
	if (ind == 5 && cmd->option && ft_strncmp(cmd->option, "-n", 2) != 0)
		return (print_lexerror(cmd->cmd, cmd->option));
	if (ind != 4)
	{
		cmd->arg = expander(cmd->arg, env, ex_status);
		cmd->input = expander(cmd->input, env, ex_status);
	}
	return (0);
}

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

int	command_lexer(t_cmd *c, char **env, int ex_status)
{
	int		i;
	int		ind;

	i = 0;
	while (c[i].cmd)
	{
		ind = own_check(c[i].cmd);
		if (ind > 0)
		{
			if (own_lexer(&c[i], ind, env, ex_status) == -1)
				return (-1);
		}
		else
			c[i].input = expander(c[i].input, env, ex_status);
		if (remove_quotation(&c[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
