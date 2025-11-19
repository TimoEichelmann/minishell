/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:15:37 by snegi             #+#    #+#             */
/*   Updated: 2025/11/19 14:52:38 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	append_input_to_file(char *delimiter, int file)
{
	char	*input;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	input = readline("> ");
	while (input != NULL) 
	{
		if (ft_strncmp(input, delimiter, ft_strlen(delimiter) + 1) == 0) 
		{
			free(input);
			break ;
		}
		write(file, input, strlen(input));
		write(file, "\n", 1);
		free(input);
		input = readline("> ");
	}
}

void	redirect_input(char **delimiter, int count, t_shell *shell)
{
	int	i;

	i = 0;
	shell->file = open("tempfile.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->file == -1)
		return ;
	while (i < count)
		append_input_to_file(delimiter[i++], shell->file);
	close(shell->file);
	shell->file = open("tempfile.txt", O_RDONLY);
	dup2(shell->file, 0);
	close(shell->file);
}

void	check_docinput(t_cmd *cmd, t_shell *shell)
{
	int		i;
	char	**delimiter;
	int		count;
	int		j;

	i = -1;
	count = 0;
	while (cmd->red && cmd->red[++i] != NULL)
	{
		if (cmd->red != NULL && cmd->red[i][0] == '4')
			count++;
	}
	delimiter = malloc(sizeof(char *) * (count + 1));
	i = -1;
	j = 0;
	while (cmd->red && cmd->red[++i] != NULL)
	{
		if (cmd->red != NULL && cmd->red[i][0] == '4')
			delimiter[j++] = ft_strdup(cmd->red[i] + 2);
	}
	delimiter[count] = NULL;
	redirect_input(delimiter, count, shell);
	free_delimiter(delimiter);
}

void	open_file(char *red, t_shell *shell)
{
	if (red[0] == '1' || red[0] == '2')
	{
		if (red[0] == '1')
			shell->ofile = open(red + 2, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (red[0] == '2')
			shell->ofile = open(red + 2, 
					O_CREAT | O_RDWR | O_APPEND, 0644);
		if (shell->ofile < 0)
		{
			printf("%s :No such file /wrong permission\n", red + 2);
			exit(1);
		}
		dup2(shell->ofile, 1);
		close(shell->ofile);
	}
}

void	token_check(t_cmd *cmd, t_shell *shell)
{
	int	i;

	i = -1;
	shell->file = 0;
	shell->ofile = 0;
	if (cmd->red)
		check_docinput(cmd, shell);
	while (cmd->red && cmd->red[++i] != NULL)
	{
		if (cmd->red[i][0] == '3')
		{
			if (cmd->red[i][0] == '3')
				shell->file = open(cmd->red[i] + 2, O_RDONLY);
			if (shell->file < 0)
			{
				printf("%s :No such file /wrong permission\n", cmd->red[i] + 2);
				exit(1);
			}
			dup2(shell->file, 0);
			close(shell->file);
		}
		else
			open_file(cmd->red[i], shell);
	}
}
