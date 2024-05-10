/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:41:42 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/10 13:08:17 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*paste_ex_status(char *str, int ex_status)
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

char	*paste_tilde(int index, char *str, char *result, char **env)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (i < index)
	{
		result[i] = str[i];
		i++;
	}
	j += ft_strlcpy(result + i,
			ft_getenv(env, "HOME\0"), ft_strlen(ft_getenv(env, "HOME\0") - 1));
	i++;
	while (str[i])
	{
		result[i + j] = str[i];
		i++;
	}
	result[j + i] = 0;
	free(str);
	return (result);
}

char	*tilde_expansion(char *str, int index, char **env)
{
	int		i;
	int		count;
	char	*result;

	i = 0;
	count = 0;
	while (i < index)
	{
		if (str[i] == 34)
			count++;
		i++;
	}
	if (count % 2 == 1)
		return (str);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1
				+ ft_strlen(ft_getenv(env, "HOME\0"))));
	return (paste_tilde(index, str, result, env));
}

char	*expander(char *str, char **env, int ex_status)
{
	t_count	c;
	char	*arg;

	c.i = 0;
	c.quote_count = 0;
	while (str && str[c.i])
	{
		if (str[c.i] == 39)
			c.quote_count++;
		if (str[c.i] == '$' && str[c.i + 1] == '?' && c.quote_count % 2 != 1)
			str = paste_ex_status(str, ex_status);
		if (str[c.i] == '$' && c.quote_count % 2 != 1 && str[c.i + 1]
			&& ft_isprint(str[c.i + 1]) == 1 && str[c.i + 1] != '?'
				&& ft_isalpha(str[c.i + 1]) == 1)
		{
			arg = str;
			str = exchange(arg, c.i, env);
		}
		if (str[c.i] == '~' && c.quote_count % 2 != 1)
			str = tilde_expansion(str, c.i, env);
		c.i++;
	}
	return (str);
}
