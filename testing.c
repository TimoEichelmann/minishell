/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:29:28 by teichelm          #+#    #+#             */
/*   Updated: 2024/05/29 15:50:09 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change(char *tmp, char *s)
{
	tmp[3] = s[0];
	return ;
}


int main (int argc, char **argv)
{
	char *tmp = malloc(sizeof(char) * 6);
	char *s = malloc(sizeof(char) * (2));
	tmp[0] = 'h';
	tmp[1] = 'e';
	tmp[2] = 'l';
	tmp[3] = 'l';
	tmp[4] = 'o';
	tmp[5] = 0;
	s[0] = 'u';
	s[1] = 0;
	printf("%s\n", tmp);
	change(tmp, s);
	printf("%s\n", tmp);
	free(s);
	free(tmp);
}