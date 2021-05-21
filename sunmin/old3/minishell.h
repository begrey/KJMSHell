#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "../../libft/libft.h"

typedef struct s_env
{
	char				*key;
	char				*value;
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
	struct s_line		*prev;
	struct s_line		*next;
}				t_line;

//		전역변수
int		ft_errno;
t_env	*env;
char	**stream;


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
void		exec_cd(t_line **command_line);

//		exec.c
void		ft_exec(t_line **command_line);

//		util_str.c
int			ft_strcmp(char *dest, char *src);
char		*str_append1(char *s1, char *s2);
char		*str_append2(char *s1, char *s2);
char		*str_append3(char *s1, char c);
int			is_alpha(char c);
int			is_dollar(char c);
char	*str_appendchar(char *s1, char c);

//		util_envlist.c
t_env		*ft_envnew(void *key, void *value);
void		ft_envadd_back(t_env **lst, t_env *new);
t_env		*ft_envfind(t_env **lst, char *s);
t_env		*ft_envlast(t_env *lst);

//		util_envlist2.c
char		*find_key(const char *str);
char		*find_value(const char *str);

//		util_redirection.c
void		set_redirection(t_line **line, char *redir_line);
void		go_redir(char *redir_stream);


//		init_env.c
int			init_env(char *envp[]);

//		ft_export.c
void		exec_export(t_line **command_line);
void		exec_env(t_line **command_line);
void		exec_unset(t_line **command_line);
char		*extract_env(char *str);

//		ft_other_command.c
void		other_command(t_line **comand_line);

//		ft_split_quote.c
char		**ft_split_quote(const char *str);
int			is_space(const char c);		//  나중에 util로 빼기
char		flag_check(const char c, char flag); // util
int			is_quote(const char c);		// util로 빼기

//		convert_env.c
char		*convert_env(const char *str);

//		redir_syn_check.c
int			redir_syn_check(t_line **line);

//		split_by_null.c
void		split_by_semi(t_line **line);

//		redirection.c
int			ft_redirection(t_line **line);
int			which_redir(char *s);

//		token_syn_check.c
int			token_syn_check(t_line **line);

//		parse.c
int			is_token(char *s);

#endif
