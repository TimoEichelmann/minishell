#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:18:06 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/19 17:21:37 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **ev)
{
	char **env;
	t_cmd cmd;

	cmd.arg = argv[1];

	argc = 0;
	env = init_env(ev);
	export(&env, &cmd);
	ft_env(env);
	printf("%s\n", ft_getenv(env, "abc"));
	ft_unset(env, "abc\0");
	ft_env(env);
	del_env(env);
}