#include "minishell.h"


void	put_return(int ret, t_env *env)
{
	t_env *temp;
	char	*num;

	temp = env;
	num = ft_itoa(ret);
	while (temp)
	{
		if (temp->key[0] == '?')
		{
			temp->value = num;		// free 해줘야 함
		}
		temp = temp->next;
	}
}

void	printf_return(t_env *env)		// 쓸 필요 없을 것 같음
{
	t_env *temp;

	temp = env;
	while (temp)
	{
		if (temp->key[0] == '?')
		{
			printf("%s\n", temp->value);
		}
		temp = temp->next;
	}
}

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
