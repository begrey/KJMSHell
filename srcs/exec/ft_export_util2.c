/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:00:54 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 14:07:07 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	printf_export(t_env *env)
{
	t_env	*idx;

	ft_env_sort(&env);
	idx = env;
	while (idx)
	{
		if (idx->key[0] != '?')
		{
			printf("declare -x %s", idx->key);
			if (idx->if_value)
				printf("=\"%s\"", idx->value);
			printf("\n");
		}
		idx = idx->next;
	}
}

int		is_alpha_dollar_str(char *s)
{
	char	*str;

	str = (char *)s;
	while (*str)
	{
		if (!(*str >= 'A' && *str <= 'Z') &&
				!(*str >= 'a' && *str <= 'z') && *str != '$')
			return (0);
		str++;
	}
	return (1);
}