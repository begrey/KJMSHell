#include "minishell.h"

static char		*exact_envstr(char *str)
{
	char	*s;
	int		len;
	int		i;
	char	*res;

	s = (char *)str;
	if (*s == '$')
		s++;
	len = 1;
	if (*s == '?')
	{
		res = (char *)malloc(sizeof(char) * 3);
		res[0] = '$';
		res[1] = '?';
		res[2] = '\0';
		return (res);
	}
	while (((*s >= 'A' && *s <= 'Z') || (*s >= 'a' && *s <= 'z') || (*s == '?')))
	{
		s++;
		len++;
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	return (res);
}

static int		if_env_dollar(char c1, char c2) // $ 단독, $# 특수문자 체크 (일단 문자, ?만 와야)
{
	if (c1 == '$')
	{
		if ((c2 >= 'A' && c2 <= 'Z') || (c2 >= 'a' && c2 <= 'z') || (c2 == '?'))
			return (1);
	}
	return (0);
} 

static int		check_flag(char c, int flag)
{
	if (flag == 0)
	{			
		if (c == '\'')
			flag = 1;
	}
	else
	{
		if (c == '\'')
			flag = 0;
	}

	return (flag);
}


static int		check_env_len(const char *str)	// 플래그를 고려 안해도 됨(그런 인풋만 들어옴)
{
	char	*s;
	int		len;

	len = 0;
	s = (char *)str;
	if (*s == '$')
		s++;
	if (*s == '?')
		return (1);
	while (*s && is_alpha(*s))
	{
			len++;
		s++;
	}
	return (len);
}

static int		if_effective(const char *str, int flag)
{
	char	*s;


	s = (char *)str;

		if (!flag)
		{
			if (if_env_dollar(*s, *(s + 1)))
			{
				return (check_env_len(s));		// $USER=sunmin 이라고 치면 5를 반환
			}
		}
	return (0);
}

static int		get_new_len(const char *str, t_env *env)
{
	char	*s;
	int		env_len;
	int		env_var_len;
	int		new_len;
	int		flag;		// ' 작은 따옴표일때만 켜짐 (플래그 켜지면 convert 적용 안함)

	flag = 0;
	new_len = 0;
	env_len = 0;
	s = (char *)str;
	while (*s)
	{
		flag = check_flag(*s, flag);
		if ((env_len = if_effective(s, flag)))
		{
			env_var_len = ft_strlen(extract_env(exact_envstr(s), env));
			s = s + env_len;
			new_len += env_var_len;
		}
		else
		{
			s++;
			new_len++;
		}
	}
	return (new_len);
}

char		*convert_env(char *str, t_env *env)
{
	char	*s;
	int		env_len;
	int		new_len;
	char	*result;
	int		flag;
	char	*temp;

//	result = NULL;
	flag = 0;
	result = ft_strdup("");
	new_len = get_new_len(str, env);

//	result = (char *)malloc(sizeof(new_len + 1));


//	result[new_len] = '\0';

	env_len = 0;
	s = (char *)str;

	while (*s)
	{
		flag = check_flag(*s, flag);
		if ((env_len = if_effective(s, flag)))
		{
			temp = result;
//			result = str_append2(result, extract_env(exact_envstr(s), env));
			result = ft_strjoin(result, extract_env(exact_envstr(s), env));
			free(temp);
			s = s + env_len;
		}
		else
		{
			temp = result;
			result = str_append3(result, *s);
	//		free(temp);
		}
		s++;

	}
	return (result);
}


/*
int		main(void)
{
	char	*str;
	char	**split;
	int		i;

	str = ft_strdup("echo a$USER\"$USER\"$USERa $USER \'$USER\'");
	printf("input :%s\n", str);
	split = ft_split_quote(str);
	i = 0;
	while (split[i])
	{
		split[i] = convert_env(split[i]);
		printf("split[i] :%s\n", split[i]);
		i++;
	}
	return (0);
}
*/
