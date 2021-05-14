
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

static int	get_word_num(const char *str)
{
	char	**split;
	char	*s;
	char	flag;
	int		word_num;
	int		len;
	int		split_point;

	split = NULL;
	s = (char *)str;
	len = 0;
	while (is_space(*s))
		s++;
	if (*s)
		word_num = 1;
	else
	{
		word_num = 0;
		return (0);
	}									
	flag = '\0';
	split_point = 0;


	while (*s)
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
			split_point = word_num;
		}
		s++;
	}
	return (word_num);
}

static char	**new_string(const char **split, int word_num)
{
	char	**new_split;


	return new_split;
}

int		*get_word_len(const char *str)
{
	char	**split;
	char	*s;
	char	flag;
	int		word_num;
	int		word_num2;		//malloc 용
	int		len;
	int		split_point;
	int		*word_len;
	int		*word_len2;

	word_num2 = get_word_num(str);
	word_len = (int *)malloc(sizeof(int) * word_num2);
	word_len2 = word_len;
	split = (char **)malloc(sizeof(char *) * (word_num2 + 1));
	split[word_num2] = NULL;
	split = NULL;
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
		if (split_point != word_num)
		{
//			split = new_string(split, word_num);
			split_point = word_num;
		}

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
					*word_len2 = len;
					word_len2++;
					len = 0;
					s--;
				}
			}
		}
		s++;
		len++;
	}
	if (len)
		*word_len2 = len;
	if (flag)
		printf("syntax error\n");
	return (word_len);
}

static char	**ft_split_quote(const char *str)
{
	char	**split;
	char	*s;
	char	flag;
	int		word_num;
	int		word_num2;		//malloc 용
	int		len;
	int		split_point;
	int		*word_len;
	int		i;

	split = NULL;
	word_num2 = get_word_num(str);
	word_len = get_word_len(str);
	split = (char **)malloc(sizeof(char *) * (word_num2 + 1));
	split[word_num2] = NULL;
	i = 0;
	while (i < word_num2)
	{
		split[i] = (char *)malloc(sizeof(char) * (word_len[i] + 1));
		split[i][word_len[i]] = '\0';
		printf("wd_len[%d] %d\n", i, word_len[i]);
		i++;
	}
	s = (char *)str;
	len = 0;
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
		if (split_point != word_num)
		{
			split_point = word_num;
		}
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
					len = 0;
					s--;
				}
			}
		}
		split[word_num - 1][len] = *s;	//	 넣기만 하면 됨
//		printf("| %c |  | %c | w_n : %d, len :%d\n", *s, flag, word_num, len);
		s++;
		len++;
	}
	if (flag)
		printf("syntax error\n");
	return (split);
}

#include "minishell.h"


int		main(void)
{
	char	*str;
	char	**split;

	str = ft_strdup("a    abc a\"a\" \'\"aa\' \' ");
//	str = ft_strdup("echo  \"\'d\'\"a   b\"   c \'  \"\'  \'  d");
	printf("input :%s\n", str);
	split = ft_split_quote(str);

	int i = 0;
	while (split[i])
	{
		printf("split[%d] :%s\n", i, split[i]);
		i++;
	}
	return (0);
}

//			echo		;'222'    ; echo    "$USER"			// ft_split_quote에서
//			echo		;'222'	  ; echo	"sunmin"
//
//			echo ; 222 ; echo eee						 뜯어내면서 리스트
//			echo -> ; -> 222 -> ; -> echo -> eee
//

