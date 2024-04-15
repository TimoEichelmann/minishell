/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:06 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/15 16:41:55 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	substr_len(char *substr)
{
	int	i;

	i = 0;
	while (substr[i] && substr[i] != ' '
		&& substr[i] != 34 && substr[i] != 39 && substr[i] != '$')
		i++;
	return (i);
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