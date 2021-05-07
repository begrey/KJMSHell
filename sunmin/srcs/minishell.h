#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../libft/libft.h"

typedef	struct	s_redirc
{
	int				type;
	char			*f_name;

}				t_redirc;			

typedef struct s_line
{
	char			*arg;
	struct t_redirc	*redirc; //리다이렉션들
	struct s_line	*line; //parsing 단계별 line
	struct s_line	*prev;
	struct s_line	*next;
}				t_line;

void		ft_listadd_back(t_line **lst, t_line *new);
t_line		*ft_listlast(t_line *lst);
t_line		*ft_listnew(char *content);
char        **ft_split_syn(char const *s, char c);

#endif
