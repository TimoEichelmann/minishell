/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:31:43 by snegi             #+#    #+#             */
/*   Updated: 2024/04/19 16:51:10 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *current_pwd()
{
        char *folder;
        int i;

        folder = getcwd(NULL, 0);
        i = ft_strlen(folder);
        while(folder[i-1] != '/')
            i--;
        if (ft_strncmp(folder + i, "minishell",9) == 0)
            folder = ">$ ";
        else
            folder = ft_strjoin(folder + i, ">$ ");
    return(folder);
}

int count_folder()
{
    char *folder;
    int count;
    int i;
    
    i = 0;
    count = 0;
    folder = getcwd(NULL, 0);
    while(folder[i] != '\0' && (ft_strncmp(folder + i, "minishell",9) != 0))
        i++;
    while (folder[i] != '\0')
    {
        if (folder[i] == '/')
            count++;
        i++;
    }
    return (count);
}

char *maintain_cd(char *input, char *promt) 
{
    char *folder;
    int count;

    while (*input != '\0' && *input == ' ')
        input++;
    if(!*input)
    {
        count = count_folder();
        while(count--)
            chdir("..");
        folder = ">$ ";
        return (folder);
    }
    if (input[0] == '.' && ft_strncmp(current_pwd(), ">$ ", 3) == 0)
        return (promt);   
    if (chdir(input) != 0)
    {
        perror("chdir");
        return (promt);
    }
    folder = current_pwd();
    return (folder);
}

