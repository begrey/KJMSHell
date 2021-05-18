/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:38:51 by jimkwon           #+#    #+#             */
/*   Updated: 2021/05/18 08:53:56 by jimkwon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <termios.h>
# include <termcap.h>
# include "../libft/libft.h"

# define BACKSPACE 127
# define U_ARROW 4283163 // 65 0 0 
# define D_ARROW 4348699
# define R_ARROW 4414235
# define L_ARROW 4479771

typedef	struct	s_redirc
{
	int				type;
	char			*f_name;

}				t_redirc;			

typedef struct s_line
{
	char				*arg;
	int					token;
//	struct s_redirc		**stream; //리다이렉션들
	struct s_line		*line; //parsing 단계별 line
	struct s_line		*prev;
	struct s_line		*next;
}				t_line;

//		ft_listadd_back.c
void		ft_listadd_back(t_line **lst, t_line *new);

//		ft_listlast.c
t_line		*ft_listlast(t_line *lst);

//		ft_listnew.c
t_line		*ft_listnew(char *content);

int		parse_line(char **line);
int		ft_strcmp(char *dest, char *src);
void	parse_token(char **line, int i);
char	*parse_command(char *line_piece, char *str);
char	*ft_echo(char *args);

#endif