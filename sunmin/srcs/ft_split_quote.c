
// 기존 스플릿 처럼 개수 다 세고 나누는 것이 아니라, 세면서 나누는 방식으로 구조를 짤 것


#include "minishell.h"

static	int	is_space(const char c)
{
	if (c == ' ' || (c >= 9 && c<= 13))
		return (1);
	return (0);
}

static	int	is_quote(const char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

static char	*new_string(const char *str)
{
	return 0;
}

static char	flag_check(const char c, char flag)
{
	if (!flag)
	{
		if (is_quote(c))
		{
			if (c == '\'')
				flag = '\'';
			else
				flag = '\"';
		}
	}
	else
	{
		if (c == flag)
			flag = '\0';
	}
	return (flag);
}

static char	**ft_split_quote(const char *str)
{
	char	**split;
	char	*s;
	char	flag;
	int		word_num;
	int		len;
	int		split_point;

	s = (char *)str;
	len = 0;						// 변수 초기화
	while (is_space(*s))
		s++;
	if (*s)
		word_num = 1;
	else
	{
		word_num = 0;
		return (NULL);		// 2차원 빈문자열 반환해야
	}									
	flag = '\0';
	split_point = 0;


	while (*s)			// 개수 체크하면서 스플릿
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (is_space(*s))
			{
				while (is_space(*s))
					s++;
				if (*s)
				{
					word_num++;
					s--;
				}
			}
		}
		if (split_point != word_num)
		{
			new_string();		// 여기 하면 됨
			split_point = word_num;
		}
		printf("| %c |  | %c | w_n : %d, len :%d\n", *s, flag, word_num, len);
		s++;
	}
	return (split);
}

#include "minishell.h"


int		main(void)
{
	char	*str;
	char	**split;

	str = ft_strdup("echo  'd'a   b   c   \"    d\"");
	printf("input :%s\n", str);
	split = ft_split_quote(str);
	return (0);
}
