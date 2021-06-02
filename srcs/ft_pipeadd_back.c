/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipeadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:39:36 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/02 16:41:09 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_pipeadd_back(t_pipe **pip, t_pipe *new)
{
	t_pipe	*last;
	t_pipe	*temp;

	temp = *pip;
	if (temp == NULL)
	{
		*pip = new;
		new->next = NULL;
		return ;
	}
	temp = *pip;
	last = ft_pipelast(temp);
	last->next = new;
}
