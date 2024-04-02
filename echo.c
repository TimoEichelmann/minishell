/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 17:39:59 by marvin            #+#    #+#             */
/*   Updated: 2024/03/29 17:39:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//if echo is called just pass in string "..." to be echoed or Variable

int	substr_len(char *substr)
{
	int	i;

	i = 1;
	while (substr[i] && substr[i] != ' ')
		i++;
	return (i);
}

char	*ft_getenv(char *p)
{
	return ("hello\0");
}

t_list	*variables(char *str)
{
	t_list	*list;
	t_list	*node;
	t_variables	*content;
	int	i;
	
	i = 0;
	list = NULL;
	while (str[i])
	{
		if (str[i] == '$' && ft_isprint(str[i + 1]) == 1)
		{
			node = malloc(sizeof(t_list));
			content = malloc(sizeof(t_variables));
			content->name = ft_substr(str, i, substr_len(str + i));
			content->val = ft_getenv(content->name + 1);
			if (!content->val)
				content->val = content->name;
			node->content = (void *)content;
			node->next = NULL;
			i += ft_strlen(content->name);
			ft_lstadd_back(&list, node);
		}
		i++;
	}
	return (list);
}

int	final_length(t_list	*vars, char *str)
{
	int	strlen;
	int	final_len;
	int	namelen;
	int	vallen;
	t_variables	*c;

	namelen = 0;
	vallen = 0;
	strlen = ft_strlen(str);
	while (vars)
	{
		c = (t_variables *)vars->content;
		namelen += ft_strlen(c->name);
		vallen += ft_strlen(c->val);
		vars = vars->next;
	}
	final_len = strlen - namelen + vallen + 1;
	printf("%d %d %d %d\n", namelen, vallen, final_len, strlen);
	return (final_len);
}

void	ft_free(t_list *list, char *final)
{
	t_list	*temp;
	t_variables	*c;

	while (list->next)
	{
		c = (t_variables *)list->content;
		free(c->name);
		free(list->content);
		temp = list;
		list = list->next;
		free(temp);
	}
	free(final);
}

void	echo(char *str)
{
	int		i;
	int		j;
	t_list	*v;
	char	*final;
	t_list	*start;
	t_variables	*c;

	i = 0;
	j = 0;
	v = variables(str);
	start = v;
	final = malloc(sizeof(char) * final_length(v, str));
	while(str[j])
	{
		if (str[j] == '$' && ft_isprint(str[j + 1]) == 1)
		{
			c = (t_variables *)v->content;
			ft_strlcpy(final + i, c->val, ft_strlen(c->val));
			printf("%s\n %d %d\n", c->val, ft_strlen(c->name), ft_strlen(c->val));
			i += ft_strlen(c->val) - 1;
			j += ft_strlen(c->name) - 1;
			v = v->next;
		}
		else
			final[i] = str[j];
		i++;
		j++;
	}
	printf("%c\n", final[7]);
	final[i] = '\0';
	printf("%s\n", final);
	ft_free(start, final);
}

int	main(void)
{
	char *p;
	p = malloc(sizeof(char) * 10);
	p[0] = 'h';
	p[1] = '$';
	p[2] = 'h';
	p[3] = ' ';
	p[4] = '$';
	p[5] = 'y';
	p[6] = ' ';
	p[7] = '7';
	p[8] = '8';
	p[9] = '\0';
	//printf("%s\n", p);
	echo(p);

}