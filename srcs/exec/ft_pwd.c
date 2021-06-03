/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 17:23:37 by jimkwon           #+#    #+#             */
/*   Updated: 2021/06/03 11:22:04 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void		ft_pwd(int pip_flag, t_env *env)
{
	char	*str;
	char	*buf;

	buf = NULL;
	str = getcwd(buf, 1);
	printf("%s\n", str);
	free(str);
	if (pip_flag == 0)
		exit(0);
	else
		put_return(0, env);
}
