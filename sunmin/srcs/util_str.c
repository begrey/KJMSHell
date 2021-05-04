#include "./minishell.h"

int		is_alpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int		is_dollar(char c)
{
	if (c == '$')
		return (1);
	return (0);
}

char	*ft_joinfree(char **s1, char **s2)
{
	char *str;

	str = ft_strjoin(*s1, *s2);
	free(*s1);
	free(*s2);
	return (str);
}

char	*str_append(char *s1, char *s2)
{
	char	*str;

	str = ft_joinfree(&s1, &s2);
	return (str);
}
