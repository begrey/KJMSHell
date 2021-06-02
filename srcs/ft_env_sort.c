/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 14:50:43 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/02 17:38:41 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_env_sort(t_env **env)
{
	t_env	*repeat;
	t_env	*again;
	char	*tmp;

	again = *env;
	while (again)
	{
		repeat = *env;
		while (repeat)
		{
			if (repeat->next && ft_strcmp(repeat->key, repeat->next->key) > 0)
			{
				tmp = (repeat->key);
				repeat->key = (repeat->next->key);
				repeat->next->key = (tmp);
				tmp = (repeat->value);
				repeat->value = (repeat->next->value);
				repeat->next->value = (tmp);
			}
			repeat = repeat->next;
		}
		again = again->next;
	}
}
