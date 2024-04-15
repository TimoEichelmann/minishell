/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:20:25 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/15 15:20:34 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_env(t_list **env, char *input)
{
	int	i;
	int	j;
	t_list	*new;
	char	*var;

	i = 0;
	j = 0;
	new = malloc(sizeof(t_list));
	// var = (char *)new->c;
	new->c = malloc(sizeof(char) * ft_strlen(input) + 1);
	var = new->c;
	ft_strlcpy(var, input, ft_strlen(input) + 1);
	ft_lstadd_back(env, new);
}


void	ft_unset(t_list **env, char *name)
{
	t_list	*p;
	t_list	*temp;

	while (*name == ' ')
		name++;
	p = *env;
	while (p->next && ft_strncmp((char *)p->next->c, name, ft_strlen(name)) != 0)
		p = p->next;
	if (p->next)
	{
		temp = p->next;
		p->next = p->next->next;
		free(temp->c);
		free(temp);
	}
	else
	{
		temp = p->next;
		free(temp->c);
		free(temp);
		p->next = NULL;
	}
}

void    ft_export(t_list **env, char *input)
{
    char *name;
    int i;
	char	*val;

	i = 0;
    while (*input && *input == ' ')
        input++;
    if (*input)
    {
        while (input[i] && input[i] != '=')
            i++;
		if (!input[i + 1] || (input[i] == '=' && !input[i + 1]))
		{
			printf("Usage: export NAME=value\n");
			return ;
		}
		name = ft_substr(input, 0, i);
		val = ft_getenv(*env, name);
		if (!val)
			new_env(env, input);
		else
		{
			ft_unset(env, name);
			new_env(env, input);
			// change_env(env, name, input);
		}
		free(name);
    }
    else
        printf("Invalid argument format for export\n");
}