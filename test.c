/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:29:12 by timo              #+#    #+#             */
/*   Updated: 2024/05/28 17:46:16 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//start = index of cut place len == char * len u want to cut
char	*cut_str(char *str, int start, int len)
{
	char	*new;
	int		i;

	i = start;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (ft_strlen(str) - len + 1 <= 1)
	{
		free(str);
		return (NULL);
	}
	ft_strlcpy(new, str, start);
	while (i < len)
		i++;
	ft_strlcpy(new + start, str + start + len, ft_strlen(str + start + len));
	free(str);
	return (new);
}

//fill = str to pace     start = index of position to pace in    len = len of charachter to be taken from fill
char	*paste_str(char *str, char *fill, int start, int len)
{
	char	*new;
	int		i;

	if (!fill)
		return (str);
	if (!str)
		return (ft_strdup(fill));
	new = malloc(sizeof(char) * (ft_strlen(str) + len + 1));
	ft_strlcpy(new, str, start);
	ft_strlcpy(new + start, fill, len);
	ft_strlcpy(new + ft_strlen(new), str + start, ft_strlen(str));
	free(str);
	return (new);
}
int	split_size(char *str, int *q1, int *q2, char ch)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	c.count = 1;
	while (str[c.i])
	{
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (str[c.i] == ch && ((c.qcount39 % 2 || c.qcount34 % 2) != 1))
			c.count++;
		c.i++;
	}
	if (q1 && q2)
	{
		*q1 = 0;
		*q2 = 0;
	}
	return (c.count);
}

char	**split_cmds(char *str, char ch)
{
	t_count c;
	char	**result;

	c.i = 0;
	c.j = 0;
	c.count = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	result = malloc(sizeof(char *) * (split_size(str, &c.qcount39, &c.qcount34, ch) + 1));
	while (str[c.i])
	{
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (str[c.i] == ch && ((c.qcount39 % 2 || c.qcount34 % 2) != 1))
		{
			result[c.count++] = ft_substr(str, c.j, c.i - c.j);
			c.j = c.i + 1;
		}
		if (!str[c.i + 1])
			result[c.count++] = ft_substr(str, c.j, c.i - c.j + 1);
		c.i++;
	}
	result[c.count] = NULL;
	return (result);
}

int	var_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != ' ' && var[i] != '<' && var[i] != '>'
		&& var[i] != 34 && var[i] != 39 && var[i] != '$')
		i++;
	return (i);
}

char	*paste_exit_status(char *str, int ex, int i)
{
	str = cut_str(str, i, 2);
	str = paste_str(str, ft_itoa(ex), i, ft_strlen(ft_itoa(ex)) + 1);
	return (str);
}

char	*expander(char *str, char **env, int ex)
{
	t_count c;
	char	*var;

	c.i = 0;
	c.qcount39 = 0;
	c.qcount34 = 0;
	while (str[c.i])
	{
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (str[c.i] == '$' && c.qcount39 % 2 != 1 && str[c.i + 1] == '?')
			str = paste_exit_status(str, ex, c.i);
		if (str[c.i] == '$' && c.qcount39 % 2 != 1)
		{
			var = ft_substr(str, c.i + 1, var_len(str + c.i + 1));
			str = cut_str(str, c.i, var_len(str + c.i + 1) + 1);
			str = paste_str(str, getenv(var), c.i, ft_strlen(getenv(var)) + 1);
			free(var);
			c.i--;
		}
		c.i++;
	}
	return (str);
}

char	*remover(char *str)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (str[c.i])
	{
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			str = cut_str(str, c.i, 1);
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			str = cut_str(str, c.i, 1);
		c.i++;
	}
	return (str);
}

int	redirect_need(char *str)
{
	t_count	c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (str[c.i])
	{
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if ((str[c.i] == '<' || str[c.i] == '>') && (c.qcount34 % 2 || c.qcount39 % 2) != 1)
			return (1);
		c.i++;
	}
	return (0);
}

int	realloc_redirect(char ***red)
{
	char	**r;
	char	**r2;
	int		i;
	
	if (!*red)
	{
		*red = malloc(sizeof(char *) * 2);
		return (0);
	}
	i = 0;
	r = *red;
	while (r[i])
		i++;
	*red = malloc(sizeof(char *) * (i + 1));
	i = 0;
	r2 = *red;
	while (r[i])
	{
		r2[i] = r[i];
		i++;
	}
	free(r);
	return (i);
}

int	file_length(char *s)
{
	
}

void	parse_redirect(char *str, char **red, int i)
{
	char	c;

	c = str[i];
	while (str[i++] == c)
	while(str[i++] == ' ')
	if (!*red)
	{
		*red = malloc(sizeof(char *) * 2);
	}
	else
		*red = malloc(sizeof(char *) * )
}

char	**redirect(char **str, char **red)
{
	t_count c;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (str[c.i])
	{
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if ((str[c.i] == '<' || str[c.i] == '>')
			&& (c.qcount34 % 2 || c.qcount39 % 2) != 1)
		{
			parse_redirect(str, red, c.i);
			c.i--;
		}
		c.i++;
	}
}

void	parser(char *cmd, t_cmd *res, char **env)
{
	res->cmd = split_cmds(cmd, ' ');
	res->end = 1;
	res->red = NULL;
	int i = 0;
	while(res->cmd[i])
	{
		res->cmd[i] = expander(res->cmd[i], env, 5);
		res->red = redirect(&res->cmd[i], res->red);
		res->cmd[i] = remover(res->cmd[i]);
		printf("%s ", res->cmd[i++]);
	}
	printf("\n");
}

t_cmd *creator(char *input, char **env)
{
	char 	**splitted;
	t_cmd	*cmd;
	char *temp;
	int		i;

	i = 0;
	splitted = split_cmds(input, '|');
	while (splitted[i])
	{
		temp = splitted[i];
		splitted[i] = ft_strtrim(splitted[i], " ");
		free(temp);
		i++;
	}
	i = 0;
	cmd = malloc(sizeof(t_cmd) * (split_size(input, NULL, NULL, '|') + 1));
	free(input);
	while (splitted[i])
	{
		parser(splitted[i], &cmd[i], env);
		i++;
	}
	cmd[i].end = 0;
	return (cmd);
}

int main(int argc, char **argv, char **env)
{
	char *s = readline(">");
	t_cmd *res = creator(s, env);
}