/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 13:49:02 by sunmin            #+#    #+#             */
/*   Updated: 2021/06/03 13:55:51 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_single_env(t_env *env)
{
	t_env *temp;

	temp = env;
	free(temp->key);
	free(temp->value);
	free(temp);
}

void	exec_unset(t_line *line, t_env *env, int pip_flag)
{
	t_env	*now;
	t_env	*begin;
	t_line	*temp;

	temp = line->next;
	while (temp)
	{
		begin = env;
		while (begin)
		{
			if ((now = ft_envfind(&env, temp->arg)))
			{
				if (now->prev)
					now->prev->next = now->next;
				if (now->next)
					now->next->prev = now->prev;
				free_single_env(now);
			}
			begin = begin->next;
		}
		temp = temp->next;
	}
	if (pip_flag == 0)
		exit(0);
}
