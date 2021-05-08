#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include "../../libft/libft.h"

typedef struct s_env
{
	char				*key;
	char				*value;
	int					if_value;
	struct s_env		*next;
}				t_env;

typedef	struct	s_redirc
{
	int				type;
	char			*f_name;

}				t_redirc;			

typedef struct s_line
{
	char				*arg;
	struct s_redirc		*si; //리다이렉션들
	struct s_redirc		*so; //리다이렉션들
	struct s_line		*line; //parsing 단계별 line
	struct s_line		*prev;
	struct s_line		*next;
}				t_line;

t_env	*env;

//		ft_listadd_back.c
void		ft_listadd_back(t_line **lst, t_line *new);

//		ft_listlast.c
t_line		*ft_listlast(t_line *lst);

//		ft_listnew.c
t_line		*ft_listnew(char *content);

//		ft_split_syn.c
char        **ft_split_syn(char const *s, char c);

//		parse_line.c
int			parse_line(char **line);

//		ft_pwd.c
void		exec_pwd(void);
void	exec_cd(t_line **command_line);

//		ft_exec.c
void		ft_exec(t_line **command_line);

//		util_str.c
int			ft_strcmp(char *dest, char *src);
char		*str_append1(char *s1, char *s2);
char		*str_append2(char *s1, char *s2);
int			is_alpha(char c);
int			is_dollar(char c);

//		util_envlist.c
t_env		*ft_envnew(void *key, void *value);
void		ft_envadd_back(t_env **lst, t_env *new);
t_env		*ft_envfind(t_env **lst, char *s);
t_env		*ft_envlast(t_env *lst);

//		util_envlist2.c
char		*find_key(const char *str);
char		*find_value(const char *str);

//		init_env.c
int			init_env(char *envp[]);

//		exec_export.c
void		exec_export(t_line **command_line);
void		exec_env(t_line **command_line);
void		exec_unset(t_line **command_line);
char		*extract_env(char *str);


#endif
