/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 12:42:42 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/15 15:56:42 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

int	iterate_quotes(char *input, int ind, int i)
{
	int	quote_count;
	int	quote_check;

	quote_count = 0;
	quote_check = 0;
	while (input[i])
	{
		if ((ind == 1 && input[i] == 34) || (ind == 2 && input[i] == 39))
			quote_count++;
		i++;
	}
	i = 0;
	if (quote_count % 2 == 1)
	{
		while (quote_check != quote_count)
		{
			if ((ind == 1 && input[i] == 34) || (ind == 2 && input[i] == 39))
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

void	env_lexer(t_cmd *cmd)
{
	if (cmd.option)
		printf("env: '%s': No such file or directory", cmd.option);
	if (cmd.arg)
		printf("env: '%s': No such file or directory", cmd.arg);
	return (-1);
}

char	*exchange(char *arg, int index, t_env *env)
{
	char	*var;
	char	*result;
	int		i;

	i = 0;
	var = substr(arg, index + 1, substr_len(index + 1));
	result = malloc(sizeof(char) * (ft_strlen(arg) - ft_strlen(var)
				+ ft_strlen(ft_getenv(var))));
	while(i < index)
	{
		result[i] = arg[i];
		i++;
	}
	index += ft_strlcpy(result, ft_getenv(var), ft_strlen(ft_getenv(var))) - 1;
	i += ft_strlen(var) + 1;
	while(arg[i])
	{
		result[index] = arg[i];
		index++;
		i++;
	}
	result[index] = 0;
	free(arg);
	return (result);
}

void	expander(t_cmd **cmd, t_env *env)
{
	t_cmd *c;
	int		i;
	int		quote_count;

	i = 0;
	c = cmd;
	quote_count = 0;
	while (c.arg[i])
	{
		if (c.arg[i] == 39)
			quote_count++;
		if (c.arg[i] == '$' && quote_count % 2 != 1 && c.arg[i + 1]
			&& ft_isprint(c.arg[i + 1]) == 1)
			c.arg = exchange(c.arg, i, env);
		i++;
	}
}

int	own_lexer(t_cmd **c, int ind, t_env *env)
{
	t_cmd *cmd;

	cmd = *c;
	if (ind == 1 && (cmd.option || cmd.arg))
		if (env_lexer(cmd) == -1)
			return (-1);
	if (ind == 2 && cmd.option)
	{
		printf("unset: bad option: %s", cmd.option);
		return (-1);
	}
	if (ind == 4 && cmd.option)
	{
		printf("export: bad option: %s", cmd.option);
		return (-1);
	}
	if (ind == 5 && cmd.option && ft_strncmp(cmd.option, "-n", 2) != 0)
	{
		printf("echo: bad option: %s", cmd.option);
		return (-1);	
	}
	if (ind != 4)
		expander(c, env);
	return (0);
}

int	command_lexer(t_cmd **cmd, t_env *env)
{
	t_cmd *c;
	int		i;
	int		ind;

	i = 0;
	c = *cmd;
	while (cmd[i].cmd)
	{
		ind = own_check(cmd[i].cmd);
		if (ind > 0)
			if (own_lexer(&cmd[i], ind, env) == -1)
				return (-1);
		else
			expander(&cmd[i], env);
		i++;
	}
	return (0);
}

t_cmd	*parser(char *input, t_env *env)
{
	t_cmd	*cmd;
	int			cmd_count;
	int			unclosed;

	unclosed = unclosed_quotes(input);
	if (unclosed != -1)
		return (NULL);
	cmd_count = command_counter(input);
	cmd = malloc(sizeof(t_cmd) * (cmd_count + 1));
	command_parser(input, &cmd, cmd_count);
	command_lexer(&cmd, env);
	return (cmd);
}

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

int main(/* int argc, char **argv */)
{
	char *input = readline(">");
	t_cmd *r;
	// argc--;
	
	int	i = 0;
	r = parser(input);
	while (r[i].cmd)
	{
		printf("c %s o %s a %s t %s\n", r[i].cmd, r[i].option, r[i].arg, r[i].token);
		free(r[i].cmd);
		free(r[i].option);
		free(r[i].arg);
		free(r[i].token);
		i++;
	}
	free_cmd(r);
}