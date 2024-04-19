/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:20:25 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/19 17:24:17 by teichelm         ###   ########.fr       */
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

char	**copy_environment(char **old, int ind)
{
	char	**new;
	int		i;

	i = 0;
	while (old[i])
		i++;
	if (ind == 1)
		new = malloc(sizeof(char *) * (i + 2));
	if (ind == 0)
		new = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (old[i])
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i] = NULL;
	if (ind == 1)
		del_env(old);
	return (new);
}

void    export(char **env, t_cmd *cmd)
{
	int	i;
	char	*name;
	char	*val;

	i = 0;
	while (cmd->arg[i] != '=')
		i++;
	name = ft_substr(cmd->arg, 0, i - 1);
	while (env[i] && ft_strncmp(env[i], name, ft_strlen(name)))
		i++;
	if (!env[i])
	{
		copy_environment()
	}
}

void    remove_env(char **env, char *input)
{
    int i;
    int j;
    
    i = 0;
    while (*input == ' ')
        input++;
    while (env[i] != NULL)
    {
        j = ft_strlen(input);
        if((ft_strncmp(env[i], input, j) == 0) && env[i][j] == '=')
        {
            j = i;
            while (env[j] != NULL)
            {
                env[j] = env[j + 1];
                j++;
            }  
        }
        else
            i++;
    }
}
