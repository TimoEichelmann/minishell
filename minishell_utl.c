/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 11:31:43 by snegi             #+#    #+#             */
/*   Updated: 2024/04/24 11:42:16 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_folder(void)
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

void	change_pwd(char **env)
{
	char *pwd;
	char *old_pwd;
	char *temp;

	pwd = getcwd(NULL, 0);
	old_pwd = ft_getenv(env, "PWD");
	temp = pwd;
	pwd = ft_strjoin("PWD=", pwd);
	old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	free(temp);
	ft_export(&env, pwd);
	ft_export(&env, old_pwd);
	free(pwd);
	free(old_pwd);
}

int	maintain_cd(char *input, char **env) 
{
    int count;

    while (*input != '\0' && *input == ' ')
        input++;
    if(!*input)
    {
        count = count_folder();
        while(count--)
            chdir("..");
        return (0);
    } 
    if (chdir(input) != 0)
    {
        perror("chdir");
        return (1);
    }
	change_pwd(env);
    return (0);
}