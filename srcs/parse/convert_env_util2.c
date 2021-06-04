/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env_util2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 13:27:06 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/04 15:10:13 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		convert_env_append(char *s, char **result)
{
	if (*(s) != '$')
		(*result) = ft_append((*result), *(s));
}

int			if_env_dollar(char c1, char c2)
{
	if (c1 == '$')
	{
		if ((c2 >= 'A' && c2 <= 'Z') || (c2 >= 'a' && c2 <= 'z') || (c2 == '?'))
			return (1);
	}
	return (0);
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
