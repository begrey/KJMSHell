#include "./minishell.h"

int		is_alpha(char c)		// 영문자인지 체크
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int		is_dollar(char c)		//  환경변수 '$' 인지 체크
{
	if (c == '$')
		return (1);
	return (0);
}

char	*ft_joinfree1(char **s1, char **s2)		// join하면서 free까지 한번에 하기
{												// 예시 : ft_joinfree1(str, "string")
	char *str;

	str = ft_strjoin(*s1, *s2);
	free(*s1);
	return (str);
}

char	*str_append1(char *s1, char *s2)
{
	char	*str;

	str = ft_joinfree1(&s1, &s2);
	return (str);
}

char	*ft_joinfree2(char **s1, char **s2)		// joinfree1과 기능 동일
{												// 예시 : ft_joinfree1(str1, str2)
	char *str;

	str = ft_strjoin(*s1, *s2);
	free(*s1);
	free(*s2);
	return (str);
}

char	*str_append2(char *s1, char *s2)
{
	char	*str;

	str = ft_joinfree2(&s1, &s2);
	return (str);
}

void	free_split(char ***split)
{
	int		i;

	i = 0;
	while ((*split)[i])
	{
		free((*split)[i]);
		i++;
	}
	free(*split);
}

int		split_len(char **split)
{
	int		i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
