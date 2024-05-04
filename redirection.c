/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timo <timo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:15:37 by snegi             #+#    #+#             */
/*   Updated: 2024/05/04 22:38:41 by timo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input(char *delimiter, t_shell *shell)
{
	char	*input;

	shell->file = open("tempfile.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (shell->file == -1)
		return ;
	input = readline("> ");
	while (input != NULL)
	{
		if (strcmp(input, delimiter) == 0)
		{
			free(input);
			break ;
		}
		write(shell->file, input, strlen(input));
		write(shell->file, "\n", 1);
		free(input);
		input = readline("> ");
	}
	close(shell->file);
	shell->file = open("tempfile.txt", O_RDONLY);
}

int	token_check(t_cmd *cmd, t_shell *shell)
{
	shell->file = 0;
	shell->ofile = 0;
	if (cmd->ifile != NULL)
	{
		if (cmd->ired == 1)
			shell->file = open(cmd->ifile, O_RDONLY);
		if (cmd->ired == 2)
			redirect_input(cmd->ifile, shell);
		if (shell->file < 0)
			return (-1);
		dup2(shell->file, 0);
		close(shell->file);
	}
	if (cmd->ofile != NULL)
	{
		if (cmd->ored == 1)
			shell->ofile = open(cmd->ofile, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (cmd->ored == 2)
			shell->ofile = open(cmd->ofile, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (shell->ofile < 0)
			return (-1);
		dup2(shell->ofile, 1);
		close(shell->ofile);
	}
	return (0);
}
