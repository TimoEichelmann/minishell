/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:29:12 by timo              #+#    #+#             */
/*   Updated: 2024/05/21 16:17:56 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//start = index of cut place len == char * len u want to cut
char	*cut_str(char *str, int start, int len)
{
	char	*new;
	int		i;

	i = start;
	if (!str)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	ft_strlcpy(new, str, start + 1);
	printf("%s '%c'\n", new, str[start + len]);
	while (i < len)
		i++;
	ft_strlcpy(new + start, str + start + len + 1, ft_strlen(str) - i);
	free(str);
	return (new);
}

//fill = str to pace     start = index of position to pace in    len = len of charachter to be taken from fill
char	*pace_str(char *str, char *fill, int start, int len)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * ft_strlen(str) + len + 1);	
	ft_strlcpy(new, str, start);
	printf("%s\n", new);
	ft_strlcpy(new + start, fill, len);
	printf("%s\n", new);
	ft_strlcpy(new + ft_strlen(new), str + start, ft_strlen(str) - 1);
	printf("%s\n", new);
	free(str);
	return (new);
}

int main(int argc, char **argv)
{
	argc--;
	char *space = malloc(sizeof(char));
	space[0] = ' ';
	char *str = argv[1];
	str = pace_str(str, "paced\0", 3, 5);
	printf("%s\n", pace_str(str, space, 8, 1));
}