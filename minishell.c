/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:17 by snegi             #+#    #+#             */
/*   Updated: 2024/04/30 15:52:29 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	count_pipes(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
		i++;
	return (i - 1);
}

void	init(t_basic *basic)
{
	t_cmd	*cmd;

	cmd = parser(basic->input, basic->env, basic->exit_status);
	if (cmd == NULL)
	{
		printf("Not Correct format, please try again!!");
	 	return ;
	}
	 basic->pipe_num = count_pipes(cmd);
	if (basic->pipe_num < 1)
	 	single_exec(cmd, basic);
	else
		main_exec(basic, cmd);
	free_cmd(cmd);
}

int	main(int ac, char **av, char **ev)
{
	t_basic	basic;

	if (ac == 1 && !av[1])
	{
		basic.exit_status = 0;
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		basic.input = readline("$> ");
		basic.env = init_env(ev);
		while (basic.input != NULL)
		{
			if (ft_strncmp(basic.input, "", 1) != 0)
			{
				add_history(basic.input);
				init(&basic);
			}
			basic.input = readline("$> ");
		}
		del_env(basic.env);
	}
	return (0);
}
