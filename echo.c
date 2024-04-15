/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:21:00 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/15 15:21:10 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
