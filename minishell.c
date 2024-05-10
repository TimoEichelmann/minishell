/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:04:17 by snegi             #+#    #+#             */
/*   Updated: 2024/05/10 19:16:18 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	not_identifier(char *arg)
{
	printf("export: not an identifier: %s\n", arg);
	free(arg);
	return (-1);
}

int	bad_assignment(void)
{
	perror("minishell: bad assignment");
	return (-1);
}

void	sigint_handler(int signal)
{
	signal--;
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
		perror("Not Correct format, please try again!\n");
		basic->exit_status = 1;
		return ;
	}
	// int i = 0;
	// while (cmd[i].cmd)
	// {
	// 	printf("i : %s c : %s a : %s if :'%d' %s of :'%d' %s\n", cmd[i].input, cmd[i].cmd, cmd[i].arg, cmd[i].ired, cmd[i].ifile, cmd[i].ored, cmd[i].ofile);
	// 	i++;
	// }
	basic->pipe_num = count_pipes(cmd);
	if (basic->pipe_num < 1)
	{
		if (ft_strncmp(cmd->cmd, "exit", 4) == 0)
			ft_exit(basic->env, cmd);
		single_exec(cmd, basic);
	}
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
		basic.env = init_env(ev);
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		while (1)
		{
			basic.input = readline("$> ");
			// while (basic.input != NULL)
			// {
			if (basic.input == NULL || !basic.input[0])
				ft_exit(basic.env, NULL);
			if (ft_strncmp(basic.input, "", 1) != 0)
			{
				add_history(basic.input);
				init(&basic);
			}
			free(basic.input);
			// }
		}
		del_env(basic.env);
	}
	return (0);
}
