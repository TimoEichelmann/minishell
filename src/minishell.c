/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:17 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_signum = sig;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_exec_sig(int sig)
{
	if (sig == SIGINT)
		write(2, "\n", 1);
}

void	init(t_basic *basic)
{
	t_cmd	*cmd;

	if (check_command(basic->input) == 1)
	{
		basic->exit_status = 1;
		free(basic->input);
		return ;
	}
	cmd = creator(basic->input, basic->env, basic->exit_status);
	basic->pipe_num = count_pipes(cmd);
	if (basic->pipe_num < 1)
	{
		basic->exit_status = our_functions(cmd, basic);
		if (basic->exit_status == -1)
		{
			if (!basic->input)
				ft_exit(basic, cmd);
			single_exec(cmd, basic);
		}
	}
	else
		main_exec(basic, cmd);
	free_cmd(cmd);
}

void	input_check(t_basic *basic)
{
	if (basic->input == NULL)
		ft_exit(basic, NULL);
	if (ft_strncmp(basic->input, "", 1) != 0)
	{
		add_history(basic->input);
		init(basic);
	}
}

int	main(int ac, char **av, char **ev)
{
	t_basic	basic;

	if (ac == 1 && !av[1])
	{
		basic.exit_status = 0;
		basic.env = init_env(ev);
		while (1)
		{
			signal(SIGINT, handle_sig);
			signal(SIGQUIT, SIG_IGN);
			basic.input = readline("$> ");
			if (g_signum)
			{
				basic.exit_status = 128 + g_signum;
				g_signum = 0;
			}
			input_check(&basic);
		}
		del_env(basic.env);
	}
	return (0);
}
