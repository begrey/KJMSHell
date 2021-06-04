/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:36:18 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 15:07:39 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*exact_envstr(char *str)
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
	while ((is_alpha(*s) || (*s == '?')) || iis_num(*s))
	{
		s++;
		len++;
	}
	res = (char *)malloc(sizeof(char) * (len + 1));
	res[len] = '\0';
	i = -1;
	while (++i < len)
		res[i] = str[i];
	return (res);
}

int			if_effective(const char *str, int flag)
{
	char	*s;

	s = (char *)str;
	if (*s == '$' && !is_alpha(*(s + 1)) && *(s + 1) != '?')
		return (0);
	if (flag != 1)
	{
		if (if_env_dollar(*s, *(s + 1)))
		{
			return (check_env_len(s));
		}
	}
	return (0);
}

int			get_new_len(const char *str, t_env *env)
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

void		join_env_temp(char *s, char **result, t_env *env)
{
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp2 = exact_envstr(s);
	temp1 = extract_env(temp2, env);
	free(temp2);
	temp3 = *result;
	*result = ft_strjoin(*result, temp1);
	free(temp3);
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
			convert_env_append(s, &result);
		s++;
	}
	return (result);
}
