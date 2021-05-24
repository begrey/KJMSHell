#include "./minishell.h"

char		*convert_escape(char *s)
{
	char	*result;
	int		flag;
	int		i;

	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));

	i = 0;
	flag = 0;
	while (*s)
	{
		result[i] = *s;
		flag = flag_check(*s, flag);
		if (flag)
		{
			if (flag == '\"')
			{
				if ((*s) == '\\' && *(s + 1) == '$')
				{
					s++;
					i++;
					result[i] = -1 * (*s);
				}
			}
		}
		else
		{
			if ((*s) == '\\')
			{
				s++;
				i++;
				result[i] = -1 * (*s);
			}
		}
		s++;
		i++;
	}
	return (result);
}

int		check_escape(char *s)
{
	int		flag;
	int		num;

	flag = 0;
	num = 0;
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (*s == '\\')
				num++;
		}
		s++;
	}
	return (num);
}

char	*delete_escape(char *s)
{
	char		*result;
	int			num;
	int			i;
	int			flag;

	i = 0;
	flag = 0;
	num = check_escape(s);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) - num + 1));
	while (*s)
	{
		flag = flag_check(*s, flag);
		if (!flag)
		{
			if (*s == '\\')
				s++;
		}
		result[i] = *s;
		i++;
		s++;
	}
	return (result);
}

char	*restore_escape(char *s)
{
	char		*result;
	int			i;

	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	i = 0;
	while (*s)
	{
		if (*s < 0)
			*s *= -1;
		result[i] = *s;
		s++;
		i++;
	}
	return (result);
}
