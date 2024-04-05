/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:31:43 by snegi             #+#    #+#             */
/*   Updated: 2024/04/04 13:32:30 by teichelm         ###   ########.fr       */
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

// void    change_env(t_list *env, char *input)
// {
//     char *name;
//     int i;

//     while (*input && *input == ' ')
//         input++;
//     if (*input)
//     {
//         name = input;
//         while (*input && *input != '=')
//             input++;
//         if (!*input || !*(input + 1) || *(input - 1) == ' ' || *(input + 1) == ' ')
//             printf("Usage: export NAME=value\n");
//         else
//         {
//             while (*env)
//                 env++;
//             *env = ft_strjoin(name,"");
//             i = 0;
//             // while (shell->env[i] || shell->env[i] != NULL)
//             //     i++;
//             // shell->env[i] = *env;
//             // shell->env[i +1] = NULL;
//             *(env + 1) = NULL;
//         }
//     }
//     else
//         printf("Invalid argument format for export\n");
// }

void    remove_env(char **env, char *input)
{
    int i;
    int j;
    
    i = 0;
    while (*input == ' ')
        input++;
    while (env[i] != NULL)
    {
        j = ft_strlen(input);
        if((ft_strncmp(env[i], input, j) == 0) && env[i][j] == '=')
        {
            j = i;
            while (env[j] != NULL)
            {
                env[j] = env[j + 1];
                j++;
            }  
        }
        else
            i++;
    }
}
