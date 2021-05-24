/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:27:45 by jimkwon           #+#    #+#             */
/*   Updated: 2020/10/16 17:04:13 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t elt_count, size_t elt_size)
{
	void	*str;

	if (!elt_count && !elt_size)
		return (ft_strdup(""));
	if ((str = malloc(elt_count * elt_size)) == NULL)
		return (NULL);
	ft_bzero(str, elt_count * elt_size);
	return (str);
}
