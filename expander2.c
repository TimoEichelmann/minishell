/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:09 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/28 13:54:04 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_identifier(char *arg)
{
	printf("export: not an identifier: %s\n", arg);
	free(arg);
	return (-1);
}

int	bad_assignment(void)
{
	perror("minishell: bad assignment");
	return (-1);
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
		i = ft_strlen(var) + 1;
		while (arg[i + index])
		{
			arg[index] = arg[i + index];
			index++;
		}
		arg[index] = 0;
		free(var);
		return (arg);
	}
	result = paste_var(index, arg, var, env);
	free(var);
	free(arg);
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
