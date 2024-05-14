/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:43:09 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/14 12:06:21 by teichelm         ###   ########.fr       */
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

int	substr_len(char *substr)
{
	int	i;

	i = 0;
	while (substr[i] && substr[i] != ' '
		&& substr[i] != 34 && substr[i] != 39 && substr[i] != '$')
		i++;
	return (i);
}
