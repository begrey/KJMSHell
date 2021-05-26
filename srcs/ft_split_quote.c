#include "minishell.h"

static void	free_split(char **split)
{
	int		i;

	i = 0;
	while(split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	is_space(const char c)		//  나중에 util로 빼기
{
	if (c == ' ' || (c >= 9 && c<= 13))
		return (1);
	return (0);
}

int	is_quote(const char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

char	flag_check(const char c, char flag)
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
	int		split_point;

	split = NULL;
	s = (char *)str;
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
			split_point = word_num;
		s++;
	}
	return (word_num);
}

int		*get_word_len(const char *str)
{
	char	*s;
	char	flag;
	int		word_num;
	int		len;
	int		split_point;
	int		*word_len;
	int		*word_len2;

	word_len = (int *)malloc(sizeof(int) * get_word_num(str));
	word_len2 = word_len;
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
			split_point = word_num;
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
	return (word_len);
}

char		**ft_split_quote(const char *str)
{
	char	**split;
	char	*s;
	char	flag;
	int		word_num;
	int		word_num2;
	int		len;
	int		split_point;
	int		*word_len;
	int		i;

	if (str[0] == '\0')			// 없으면 그냥 엔터시 세그폴트
	{
		split = (char **)malloc(sizeof(char *) * (2));
		split[1] = NULL;
		split[0] = ft_strdup("");
		return (split);
	}

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
		return NULL;		// 2차원 빈문자열 반환해야
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
		split[word_num - 1][len] = *s;
		s++;
		len++;
	}
	if (flag)
	{
		free(word_len);
		free_split(split);
		return (0);
	}
	free(word_len);
	return (split);
}
/*
int		main(void)
{
	char	*str;
	char	**split;

	str = ft_strdup("a ;;\"abc\";;\"abc\" dd");
//	str = ft_strdup("a    abc a\"a\" \'\"aa\' \' ");
//	str = ft_strdup("a");
	printf("input :%s\n", str);
	split = ft_split_quote(str);

	int i = 0;
	while (split[i])
	{
		printf("split[%d] :%s\n", i, split[i]);
		i++;
	}
//	system("leaks a.out");
//	while (1)
//		;

	return (0);
}
*/


//			echo		;'222'    ; echo    "$USER"			// ft_split_quote에서
//			echo		;'222'	  ; echo	"sunmin"
//
//			echo ; 222 ; echo eee						 뜯어내면서 리스트
//			echo -> ; -> 222 -> ; -> echo -> eee
//

