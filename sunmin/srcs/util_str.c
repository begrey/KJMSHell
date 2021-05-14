#include "minishell.h"


int		ft_strcmp(char *dest, char *src) {
	int i = 0;
	while (dest[i] != '\0' || src[i] != '\0') {
		if (dest[i] > src[i])
			return dest[i] - src[i];
		else if (dest[i] < src[i])
			return dest[i] - src[i];
		i++;
	}
	return 0;      
}

char	*ft_joinfree1(char **s1, char **s2)
{
	char	*str;
	
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

char	*ft_joinfreechar(char **s1, char *s2)
{
	char	*str;
	
	str = ft_strjoin(*s1, s2);
	free(*s1);
	return (str);
}

char	*str_appendchar(char *s1, char c)
{
	char	*str;

	str = ft_joinfreechar(&s1, &c);
	return (str);
}

char	*ft_joinfree2(char **s1, char **s2)
{
	char	*str;

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
