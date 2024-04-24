/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snegi <snegi@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:15:37 by snegi             #+#    #+#             */
/*   Updated: 2024/04/24 11:15:39 by snegi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirect_input(char *delimiter, t_shell *shell)
{
	char *input;

    shell->file = open("tempfile.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (shell->file == -1)
        return;
    while ((input = readline("> ")) != NULL) 
    {
        if (strcmp(input, delimiter) == 0) {
            free(input);
            break;
        }
        write(shell->file, input, strlen(input));
        write(shell->file, "\n", 1);
        free(input);
    }
    close(shell->file);
    shell->file = open("tempfile.txt", O_RDONLY);
    if (shell->file == -1)
        return;
    dup2(shell->file, 0);
}

int	token_check(t_cmd *cmd, t_shell *shell)
{
	if (cmd->token != NULL && ft_strncmp(cmd->token, "<\0" , 2) == 0)
	{
		shell->file = open(cmd->file, O_RDONLY);
		if(shell->file < 0)
			return(-1);
		dup2(shell->file, 0);
	}
	else if (cmd->token != NULL && ft_strncmp(cmd->token, "<<\0" ,3) == 0)
		redirect_input(cmd->file, shell);
	else if (cmd->token != NULL && ft_strncmp(cmd->token, ">\0" , 2) == 0)
	{
		shell->file = open(cmd->file, O_TRUNC | O_CREAT | O_RDWR, 0644);
		if (shell->file < 0)
			return (-1);
		dup2(shell->file,1);
	}
	else if (cmd->token != NULL && ft_strncmp(cmd->token, ">>\0" , 3) == 0)
	{
		shell->file = open(cmd->file, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (shell->file < 0)
			return (-1);
		dup2(shell->file,1);
	}
	else
		return (0);
	close(shell->file);
	return (1);
}
