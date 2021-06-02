/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 16:42:01 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/02 16:42:26 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pipe		*ft_pipenew(void)
{
	t_pipe	*lst;

	if (!(lst = (t_pipe *)malloc(sizeof(t_pipe) * 1)))
		return (NULL);
	lst->next = NULL;
	return (lst);
}
