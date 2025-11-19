/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 11:12:34 by teichelm          #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	char	*num;

	num = ft_itoa(ex);
	str = cut_str(str, i, 2);
	str = paste_str(str, num, i, ft_strlen(num) + 1);
	free(num);
	return (str);
}

char	*expand_variable(char **env, int *i, char *str)
{
	char	*var;

	var = ft_substr(str, *i + 1, var_len(str + *i + 1));
	str = cut_str(str, *i, var_len(str + *i + 1) + 1);
	str = paste_str(str, ft_getenv(env, var),
			*i, ft_strlen(ft_getenv(env, var)) + 1);
	free(var);
	if (*i >= ft_strlen(str))
		*i = ft_strlen(str) - 1;
	else
		*i -= 1;
	return (str);
}

char	*expander(char *str, char **env, int ex)
{
	t_count	c;

	c.i = 0;
	c.q9 = 0;
	c.q4 = 0;
	while (str && str[c.i])
	{
		if (str[c.i] == 39 && c.q4 % 2 != 1)
			c.q9++;
		if (str[c.i] == 34 && c.q9 % 2 != 1)
			c.qcount34++;
		if (str[c.i] == '$' && c.q9 % 2 != 1 && str[c.i + 1] == '?')
			str = paste_exit_status(str, ex, c.i);
		if (str[c.i] == '$' && c.q9 % 2 != 1 && str[c.i + 1]
			&& ft_isalnum(str[c.i + 1]) == 1)
			str = expand_variable(env, &c.i, str);
		c.i++;
	}
	return (str);
}
