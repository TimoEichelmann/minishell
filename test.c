#include "minishell.h"
char	*word(char *p)
{
	t_count	c;

	c.i = 0;
	c.j = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (p[c.j] && p[c.j] == ' ')
		c.j++;
	while (p[c.i + c.j])
	{
		if (p[c.i + c.j] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (p[c.i + c.j] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if (c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1 && (p[c.i + c.j] == ' '
			|| p[c.i + c.j] == '	' || p[c.i + c.j] == '|'
				|| p[c.i + c.j] == '<' || p[c.i + c.j] == '>'))
			return (ft_substr(p, c.j, c.i));
		c.i++;
	}
	if (c.i + c.j == 0)
		return (NULL);
	return (ft_substr(p, c.j, c.i));
}

char	*ft_return(char *str, int i)
{
	if (i == 0)
		return (NULL);
	return (str);
}

char	*delete_redirection(char *str, int i)
{
	int		j;
	char	*len;
	int		p;

	j = 0;
	while (str[i + j] == ' ' || str[i + j] == '<' || str[i + j] == '>')
		j++;
	len = word(str + i + j);
	p = ft_strlen(len) + j;
	while (str[i + p] == ' ')
		p++;
	free(len);
	if (i > 0 && str[i - 1] != ' ')
	{
		str[i] = ' ';
		p--;
		i++;
	}
	while (str[i + p])
	{
		str[i] = str[p + i];
		i++;
	}
	str[i] = 0;
	return (ft_return(str, i));
}

char	*remove_redirection(char *str)
{
	t_count	c;
	char	*temp;

	c.i = 0;
	c.qcount34 = 0;
	c.qcount39 = 0;
	while (str && str[c.i])
	{
		if (str[c.i] == 34 && c.qcount39 % 2 != 1)
			c.qcount34++;
		if (str[c.i] == 39 && c.qcount34 % 2 != 1)
			c.qcount39++;
		if ((str[c.i] == '<' || str[c.i] == '>')
			&& c.qcount34 % 2 != 1 && c.qcount39 % 2 != 1)
		{
			delete_redirection(str, c.i);
			c.i--;
		}
		c.i++;
	}
	return (str);
}


int main (void)
{
	int i  =0;
	char *input = readline(">");
	printf("%s\n", remove_redirection(input));
}