#include "../srcs/minishell.h"

int		get_word_num(const char *str)
{
	int		num;
	char	*s;

	s = (char *)str;
	len = 0;
	while (*s)
	{

		s++;
	}
	return (num);
}

void	ft_input(const char *str)
{
	char	*s;
	char	flag;
	char	*res;
	int		num;

	flag = '\0';
	s = (char *)str;
	printf("[ft_input], %s\n", s);
	num = get_word_num(str);

	while (*s)
	{
		if (!flag)
		{
			while (*s == ' ')
				s++;
		}
		if (!flag && (*s == '\"' || *s == '\'')) // 플래그 켜기
		{
			if (*s == '\"')
				flag = '\"';
			else
				flag = '\'';
		}


//		플래그 켜졌을 때, 꺼졌을 때

		if (flag && (*s == '\"' || *s == '\''))									// 플래그 끄기
		{
			if (flag == '\"' && *str == '\"')
				flag = 0;
			if (flag == '\'' && *str == '\'')
				flag = 0;
		}
		s++;
	}
}


int		main(int argc, char **argv)
{
	printf("[input]\n");
	char	*test;
	char	c;

	test = ft_strdup("echo '\"'\" dd s\'s >a >>b <c minsungho | pwd ; ls");
	printf("[main] input @@%s@@\n", argv[1]);
	ft_input(test);
	return (0);
}
