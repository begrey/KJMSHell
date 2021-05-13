#include "../srcs/minishell.h"

static int		is_space(const char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static char		flag_on(const char *str, char flag)
{
	char	*s;

	s = (char *)str;
	if ((!flag) && (*s == '\"' || *s == '\''))
	{
		if (*s == '\"')
			flag = '\"';
		else
			flag = '\'';
	}
	return flag;
}

static char		flag_off(const char *str, char flag)
{
	char	*s;

	s = (char *)str;
	if (flag)
	{
		if (flag == '\"' && *s == '\"')
			return 1;
		else if (flag == '\'' && *s == '\'')
			return 1;
	}
	return 0;
}


static int		get_len(const char *str)
{
	int		num;
	int		word_num;
	char	*s;
	char	flag;
	int		space;

	word_num = 0;
	if (!is_space(*s))
		word_num = 1;
	space = 0;
	flag = '\0';
	s = (char *)str;
	num = 0;
	while (*s && is_space(*s))		// 첫공백 넘기고 시작
		s++;
	while (*s)
	{
		if (!flag)
		{
			flag = flag_on(s, flag);
			if (flag)
				word_num++;
		}
		else
			if (flag_off(s, flag))
			{
				flag = '\0';
				space = 0;
				word_num++;
			}
		if (!flag)
		{
			while (is_space(*s))		// 플래그가 없을 때 공백 넘겨
			{
				space = 1;
				s++;
			}
			if (!is_space(*s) && space)
			{
				word_num++;
				space = 0;
			}
		}
		num++;
		printf("@@%c@@ %d, %c, word_num %d\n", *s, num, flag, word_num);
		s++;
	}
	if (flag)
		printf("syntax error (quote)\n");
	return (num);
}

static void		ft_input(const char *str)
{
	char	*s;
	char	flag;
	char	*res;
	int		num;

	flag = '\0';
	s = (char *)str;
	printf("[input], @@%s@@\n", s);
	num = get_len(str);
	printf("%d\n", num);
	while (*s)
	{

		flag_on(s, flag);
//		플래그 켜졌을 때, 꺼졌을 때

		flag_off(s, flag);
		s++;
	}
}


int		main(int argc, char **argv)
{
	printf("[input]\n");
	char	*test;
	char	c;

	test = ft_strdup("  echo \"aaa\"b	  \'a\"aa\"\'");
//	test = ft_strdup("echo '\"'\" dd s\'s >a >>b <c minsungho | pwd ; ls");
	ft_input(test);
	return (0);
}
