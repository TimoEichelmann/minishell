/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teichelm <teichelm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 16:55:22 by teichelm          #+#    #+#             */
/*   Updated: 2024/04/26 02:29:35 by teichelm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(char *input)
{
	t_count	c;

	c.i = 0;
	c.quote_count = 0;
	c.count = 0;
	while (input[c.i])
	{
		if (input[c.i] == 34 || input[c.i] == 39)
			c.quote_count++;
		if (input[c.i] == '|' && c.quote_count % 2 != 1)
			c.count++;
		c.i++;
	}
	if (!input[c.i] && c.count == 0)
		return (1);
	else
		return (c.count);
}

int	check_quotation(char **splitted)
{
	t_count c;

	c.i = 0;
	c.quote_count = 0;
	c.count = 0;
	while(splitted[c.i])
	{
		while (splitted[c.i][c.count])
		{
			if (splitted[c.i][c.count] == 34 || splitted[c.i][c.count] == 39)
				c.quote_count++;
			c.count++;
		}
		if (c.quote_count % 2 == 1)
			return (-1);
		c.count = 0;
		c.i++;
	}
	return (0);
}

void	free_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted && splitted[i])
	{
		free(splitted[i]);
		i++;
	}
	free(splitted);
}

int	check_empty(char **splitted)
{
	t_count c;

	c.i = 0;
	c.count = 0;
	while (splitted[c.i])
	{
		while (splitted[c.i][c.count] && (splitted[c.i][c.count] == '	'
				|| splitted[c.i][c.count] == ' '))
			c.count++;
		if (c.count == ft_strlen(splitted[c.i]))
			return (-2);
		c.i++;
		c.count = 0;
	}
	return (0);
}

int	check_redirections_loop(char *s, int c1, int c2, int quote_count)
{
	int	j;

	j = 0;
	while (s[j])
	{
		if (s[j] == 34 || s[j] == 39)
			quote_count++;
		if (s[j] == '>' && quote_count % 2 != 1)
		{
			if (s[j + 1] == '>' && s[j + 2])
				j++;
			c1 += 1;
		}
		if (s[j] == '<' && quote_count % 2 != 1)
		{
			if (s[j + 1] == '<' && s[j + 2])
				j++;
			c2 += 1;
		}
		j++;
	}
	if (c1 > 1 || c2 > 1)
		return (-1);
	return (0);
}

int	before(char *str, int i)
{
	if (!str[i + 1])
	{
		free(str);
		return (-1);
	}
	if (str[i - 1] == ' ' || str[i - 1] == '	')
		return (1);
	return (0);
}

char	*realloc_redirection(char *str, int i)
{
	char	*result;
	int		j;

	j = 0;
	if (before(str, i) == -1)
		return (NULL);
	if (before(str, i) == 1)
		return (str);
	else
		result = malloc(sizeof(char) * (ft_strlen(str) + 2));
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[j] = ' ';
	while (str[j])
	{
		result[j + 1] = str[j];
		j++;
	}
	result[j + 1] = '\0';
	free(str);
	return (result);	
}

int	parse_redirections(char	**str, int i)
{
	t_count	c;
	char	*s;

	c.i = 0;
	s = str[i];
	c.count = 0;
	c.quote_count = 0;
	while (s && s[c.i])
	{
		if (s[c.i] == 34 || s[c.i] == 39)
			c.quote_count++;
		if ((s[c.i] == '<' || s[c.i] == '>') && c.quote_count % 2 != 1 
				&& s[c.i - 1] != '<' && s[c.i - 1] != '>')
		{
			str[i] = realloc_redirection(s, c.i);
			c.i += c.count;
		}
		c.count = 0;
		if (!str[i])
			return (-1);
		s = str[i];
		c.i++;	
	}
	return (0);
}

int	check_redirections(char **s)
{
	t_count c;
	int		j;
	
	c.i = 0;
	c.quote_count = 0;
	c.count = 0;
	c.count2 = 0;
	c.j = 0;
	while (s[c.i])
	{
		j = check_redirections_loop(s[c.i], c.count, c.count2, c.quote_count);
		if (j == -1)
		{
			return (-3);
		}
		j = parse_redirections(s, c.i);
		if (j == -1)
		{
			return (-3);
		}
		c.i++;
	}
	return (0);
}

int	print_check(int ind, char **splitted)
{
	if (ind == -1)
		printf("parse error due to wrong quotation\n");
	if (ind == -2)
		printf("parse error due to empty command\n");
	if (ind == -3)
		printf("parse error due to wrong redirection\n");
	free_splitted(splitted);
	return (-1);
}

char	*word(char *p)
{
	t_count	c;

	c.i = 0;
	c.j = 0;
	c.quote_count = 0;
	while(p[c.j] && (p[c.j] == '	' || p[c.j] == ' '))
		c.j++;
	while (p[c.i + c.j])
	{
		if (p[c.i + c.j] == 34 || p[c.i + c.j] == 39)
			c.quote_count++;
		if ((p[c.i + c.j] == ' ' || p[c.i + c.j] == '	') && c.quote_count % 2 != 1)
			return (ft_substr(p, c.j, c.i));
		c.i++;
	}
	if (c.i + c.j == 0)
		return (NULL);
	return (ft_substr(p, c.j, c.i));
}

char	*cmd_word_check(char *p)
{
	char	*cmd;
	int		i;

	i = 0;
	cmd = word(p);
	while (cmd[i])
	{
		if (cmd[i] == ' ' || cmd[i] == '	')
			return (cmd);
		i++;
	}
	free(cmd);
	return (NULL);
}

int	check_words(char **splitted)
{
	int		i;
	char	*cmd;

	i = 0;
	while (splitted[i])
	{
		cmd = cmd_word_check(splitted[i]);
		if (cmd != NULL)		
		{
			printf("no such command : %s\n", cmd);
			free(cmd);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	checks(char **splitted)
{
	int	ind1;
	int	ind2;
	int ind3;
	int	ind4;

	ind1 = check_quotation(splitted);
	if (ind1 < 0)
		return (print_check(ind1, splitted));
	ind2 = check_empty(splitted);
	if (ind2 < 0)
		return (print_check(ind2, splitted));
	ind3 = check_redirections(splitted);
	if (ind3 < 0)
		return (print_check(ind3, splitted));
	ind4 = check_words(splitted);
	if (ind4 < 0)
		return (print_check(ind4, splitted));
	return (0);
}

int	own_check(char *cmd)
{
	int	i;

	i = 0;
	while(cmd[i] == '	' || cmd[i] == ' ')
		i++;
	if (ft_strncmp(cmd + i, "env", 3) == 0)
		return(1);
	if (ft_strncmp(cmd + i, "unset", 5) == 0)
		return(2);
	if (ft_strncmp(cmd + i, "cd", 2) == 0)
		return(3);
    if (ft_strncmp(cmd + i, "export", 6) == 0)
		return(4);
	if (ft_strncmp(cmd + i, "echo", 4) == 0)
		return(5);
	if (ft_strncmp(cmd + i, "exit", 5) == 0)
		return(6);
	if (ft_strncmp(cmd + i, "pwd", 3) == 0)
		return (7);
	else
		return (-1);
}

char	**lexer(char *input)
{
	int	cmd_num;
	char	**splitted;

	cmd_num = count_cmds(input);
	splitted = ft_split(input, '|');
	if (checks(splitted) == -1)
		return (NULL);
	return (splitted);
}

char	*cmd_read(char *input, int ind, int *j)
{
	char	*result;
	int		i;
	
	i = 0;
	if (ind < 0)
		return (NULL);
	result = word(input + *j);
	while (result[i] == ' ' || result[i] == '	')
		i++;
	*j += ft_strlen(result) + i;
	return (result);
}

int	check_true_arg(char *input)
{
	t_count c;

	c.i = 0;
	c.quote_count = 0;
	if (!input || !input[0])
		return (-1);
	while (input[c.i])
	{
		if (input[c.i] == 34 || input[c.i] == 39)
			c.quote_count++;
		if (c.quote_count % 2 != 1 && (input[c.i] == '<' || input[c.i] == '>'))
			return (-1);
		c.i++;
	}
	return (0);
}

char	*arg_read(char *input, int ind, int *j)
{
	char	*result;
	char	*pot;
	char	*tmp;
	
	result = NULL;
	if (ind < 0)
		return (NULL);
	pot = word(input + *j);
	while (check_true_arg(pot) == 0)
	{
		tmp = result;
		result = ft_strjoin(result, " \0");
		free(tmp);
		tmp = result;
		result = ft_strjoin(result, pot);
		free(tmp);
		*j += ft_strlen(pot) + 1;
		free(pot);
		pot = word(input + *j);
	}
	if (pot)
		free(pot);
	return (result);
}

int	redirection_need(char *input)
{
	t_count	c;
	int	need;

	c.i = 0;
	need = 0;
	c.quote_count = 0;
	while (input[c.i])
	{
		if (input[c.i] == 34 || input[c.i] == 39)
			c.quote_count++;
		if ((input[c.i] == '<' && input[c.i + 1] == '<') || input[c.i] == '<')
		{
			c.i++;
			need += 5;
		}
		if ((input[c.i] == '>' && input[c.i + 1] == '>') || input[c.i] == '>')
		{
			c.i++;
			need -= 2;
		}
		c.i++;
	}
	return (need);
}

void	input_need(t_cmd *cmd, int need, char *input, int *j)
{
	char	*result;
	int		i;

	i = *j;
	if (need == -2)
	{
		cmd->ifile = NULL;
		cmd->ired = 0;
		return ;
	}
	while (input[i] != '<')
		i += 1;
	if (input[i + 1] == '<')
	{
		cmd->ired = 1;
		i++;
	}
	i += 1;
	if (input[i] == '<')
		i += 1;
	result = word(input + i);
	cmd->ifile = result;
	cmd->ired += 1;
}

void	output_need(t_cmd *cmd, int need, char *input, int *j)
{
	char	*result;
	int		i;

	i = *j;
	if (need == 5)
	{
		cmd->ofile = NULL;
		cmd->ored = 0;
		return ;
	}
	while (input[i] != '>')
		i += 1;
	i++;
	if (input[i] == '>')
	{
		cmd->ored = 1;
		i += 1;
	}
	result = word(input + i);
	cmd->ofile = result;
	cmd->ored += 1;
}

void	redirection_read(t_cmd *cmd, char *input, int *j)
{
	int	need;

	need = redirection_need(input);
	if (need == 0)
	{
		cmd->ired = 0;
		cmd->ored = 0;
		cmd->ifile = NULL;
		cmd->ofile = NULL;
		return ;
	}
	output_need(cmd, need, input, j);
	input_need(cmd, need, input, j);
}

char	*truncate_input(char *input)
{
	t_count	c;
	int		ind;
	char	*tmp;

	c.i = 0;
	ind = 0;
	c.quote_count = 0;
	while (input[c.i] && ind == 0)
	{
		if (input[c.i] == 34 || input[c.i] == 39)
			c.quote_count++;
		if ((input[c.i] == '<' || input[c.i] == '>') && c.quote_count % 2 != 1)
			ind = 1;
		c.i++;
	}
	if (!input[c.i])
		return (input);
	tmp = input;
	input = malloc(sizeof(char) * (c.i));
	ft_strlcpy(input, tmp, c.i);
	free(tmp);
	return (input);
}

int	cmd_parser(t_cmd *cmd, char *input, int pipe)
{
	int	ind;
	int	j;

	j = 0;
	while (input[j] == ' ' || input[j] == '	')
		j++;
	ind = own_check(input);
	cmd->cmd = cmd_read(input, ind, &j);
	cmd->input = ft_strdup(input);
	cmd->arg = arg_read(input, ind, &j);
	if (pipe == 1)
		cmd->token = 1;
	else
		cmd->token = 0;
	redirection_read(cmd, input, &j);
	cmd->input = truncate_input(cmd->input);
	return (0);
}

t_cmd	*cmd_creator(char **splitted)
{
	int		i;
	t_cmd	*cmd;
	int		pipe;
	
	i = 0;
	pipe = 0;
	while (splitted[i])
		i++;
	if (i > 1)
		pipe = 1;
	cmd = malloc(sizeof(t_cmd) * (i + 1));
	i = 0;
	while (splitted[i])
	{
		cmd_parser(&cmd[i], splitted[i], pipe);
		i++;
	}
	cmd[i].cmd = NULL;
	free_splitted(splitted);
	return (cmd);
}

t_cmd	*parser(char *input)
{
	char	**splitted;
	t_cmd	*cmd;
	
	cmd = NULL;
	splitted = NULL;
	if (!input[0])
		return (NULL);
	splitted = lexer(input);
	if (!splitted)
		return (NULL);
	cmd = cmd_creator(splitted);
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd)
	{
		if (cmd[i].cmd)
			free(cmd[i].cmd);
		if (cmd[i].arg)
			free(cmd[i].arg);
		if (cmd[i].input)
			free(cmd[i].input);
		if (cmd[i].ifile)
			free(cmd[i].ifile);
		if (cmd[i].ofile)
			free(cmd[i].ofile);
		i++;
	}
	free(cmd);
}

// int main(void)
// {
// 	char *input = readline(">");
// 	t_cmd *cmd = parser(input);
// 	int i =0;
// 	while (cmd[i].cmd)
// 	{
// 		printf("c %s a %s i %s ri %d ro %d rif %s rof %s\n", cmd[i].cmd, cmd[i].arg, cmd[i].input, cmd[i].ired, cmd[i].ored, cmd[i].ifile, cmd[i].ofile);
// 		i++;
// 	}
// 	free_cmd(cmd);
// 	return (0);
// }

//needs variable expasion, needs variable expansion for << or specifically not