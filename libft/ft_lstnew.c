/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 16:11:57 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/04 12:36:21 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *c)
{
	t_list	*new;

	new = (t_list *)malloc(8 + 8);
	if (!new)
		return (0);
	new->c = c;
	new->next = 0;
	return (new);
}
