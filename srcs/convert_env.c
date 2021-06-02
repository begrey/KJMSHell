/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:36:18 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/02 17:31:53 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*put_return_value(char *res)
{
	res = (char *)malloc(sizeof(char) * 3);
	res[0] = '$';
	res[1] = '?';
	res[2] = '\0';
	return (res);
}

static char	*exact_envstr(char *str)
{
	char	*s;
	int		len;
	int		i;
	char	*res;

	res = NULL;
	s = (char *)str;
	if (*s == '$')
		s++;
	len = 1;
	if (*s == '?')
		return (put_return_value(res));
	while ((is_alpha(*s) || (*s == '?')))
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

static int	if_env_dollar(char c1, char c2)
{
	if (c1 == '$')
	{
		if ((c2 >= 'A' && c2 <= 'Z') || (c2 >= 'a' && c2 <= 'z') || (c2 == '?'))
			return (1);
	}
	return (0);
}

static int	check_flag(char c, int flag)
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

static int	check_env_len(const char *str)
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

static int	if_effective(const char *str, int flag)
{
	char	*s;

	s = (char *)str;
	if (!flag)
	{
		if (if_env_dollar(*s, *(s + 1)))
		{
			return (check_env_len(s));
		}
	}
	return (0);
}

int			free_temp(char *s, t_env *env)
{
	char	*temp;
	char	*temp2;
	int		env_var_len;

	env_var_len = 0;
	temp = exact_envstr(s);
	temp2 = extract_env(temp, env);
	env_var_len = ft_strlen(temp2);
	free(temp);
	free(temp2);
	return (env_var_len);
}

static int	get_new_len(const char *str, t_env *env)
{
	char	*s;
	int		env_len;
	int		env_var_len;
	int		new_len;
	int		flag;

	flag = 0;
	new_len = 0;
	s = (char *)str;
	while (*s)
	{
		flag = check_flag(*s, flag);
		if ((env_len = if_effective(s, flag)))
		{
			env_var_len = free_temp(s, env);
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

char		*ft_append(char *s, char c)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = 0;
	if (s != NULL)
		len = ft_strlen(s);
	if (!(str = (char *)malloc(sizeof(char) * (len + 2))))
		return (NULL);
	str[len + 1] = '\0';
	while (len > 0 && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	free(s);
	return (str);
}

void		join_env_temp(char *s, char **result, t_env *env)
{
	char	*temp1;
	char	*temp2;

	temp2 = exact_envstr(s);
	temp1 = extract_env(temp2, env);
	free(temp2);
	*result = ft_strjoin(*result, temp1);
	free(temp1);
}

char		*convert_env(const char *str, t_env *env)
{
	char	*s;
	int		env_len;
	int		new_len;
	char	*result;
	int		flag;

	result = NULL;
	flag = 0;
	result = ft_strdup("");
	new_len = get_new_len(str, env);
	env_len = 0;
	s = (char *)str;
	while (*s)
	{
		flag = check_flag(*s, flag);
		if ((env_len = if_effective(s, flag)))
		{
			join_env_temp(s, &result, env);
			s = s + env_len;
		}
		else
			result = ft_append(result, *s);
		s++;
	}
	return (result);
}
