#include "minishell.h"


char	*find_key(const char *str)
{
	int		i;
	int		equal;
	char	*key;
	int		flag;
	
	flag = 0;
	key = ft_strdup((char *)str);
	equal = 0;
	i = 0;
	while (key[i])
	{
		if (key[i] == '=' && flag == 0)
		{
			equal = i;
			flag = 1;
		}
		i++;
	}
	if (equal == 0)
		equal = i;
	key[equal] = '\0';
	return (key);
}

char	*find_value(const char *str)
{
	char	*value;
	int		i;
	int		equal;
	int		flag;

	flag = 0;
	value = ft_strdup((char *)str);
	equal = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '=' && flag == 0)
		{
			equal = i;
			flag = 1;
		}
		i++;
	}
	return (value + equal + 1);
}
