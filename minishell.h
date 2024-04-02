/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:32:50 by marvin            #+#    #+#             */
/*   Updated: 2024/03/30 16:32:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include "./libft/libft.h"

typedef struct s_variables {
	char	*val;
	char	*name;
}t_variables;

#endif