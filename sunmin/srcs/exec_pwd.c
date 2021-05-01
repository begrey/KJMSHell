/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 11:21:53 by sunmin            #+#    #+#             */
/*   Updated: 2021/05/01 11:29:12 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exec_pwd(void)
{
	char	*current_path;
	char	*buf;

	buf = NULL;
	current_path = getcwd(buf, 100);
	return (current_path);
}
