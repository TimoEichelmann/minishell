/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 12:43:47 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/04 13:03:59 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst && lst)
	{
		last = ft_lstlast(*lst);
		last->next = new;
		new->next = NULL;
	}
	else
	{
		*lst = new;
		new->next = NULL;
	}
}
