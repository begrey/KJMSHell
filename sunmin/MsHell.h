/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MsHell.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sunmin <msh4287@naver.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:01:01 by sunmin            #+#    #+#             */
/*   Updated: 2021/04/27 19:22:10 by sunmin           ###   ########.fr       */
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


#define EQUAL 0
#define EXIST 1

//	main.c
int				main(int argc, char **argv, char **envp);

//	get_next_line.c
static int		push_gnl(char **remain, char *temp, char **line);
int				get_next_line(int fd, char **line);

//	libft.c
int				ft_strncmp(const char *s1, const char *s2, size_t n);
size_t			ft_strlen(const char *str);
char			*ft_strdup(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*is_new(char *s, char c);

//	ft_split.c
static int		ft_word_num(char *s, char c);
static int		chnum(char *s, int index, char c);
static char		**ft_push_split(char *s, char **split, int num, char c);
char			**ft_split(char const *s, char c);

//	util.c
int				ft_find(char *s, char key);

#endif
