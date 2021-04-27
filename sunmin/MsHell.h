/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsHell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:01:01 by sunmin            #+#    #+#             */
/*   Updated: 2021/04/27 10:38:49 by sunmin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MSHELL_H
#define MSHELL_H

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <termcap.h>
#include <stdlib.h>

char	*ft_append(char *line, char buf);
int		ft_strlen(char *s);

#endif
