#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include <errno.h>
# include "../libft/libft.h"

# define BACKSPACE 127
# define U_ARROW 4283163 // 65 0 0 
# define D_ARROW 4348699
# define R_ARROW 4414235
# define L_ARROW 4479771

typedef struct	s_cursor
{
	char			*cm; //cursor motion
	char			*ce; //cursor erase
	char			*prev_his; // 이전 명령어
	int				row;
	int				col;
}				t_cursor;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				if_value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

typedef struct s_line
{
	char				*arg;
	struct s_line		*prev;
	struct s_line		*next;
}				t_line;

//		ft_listadd_back.c
void		ft_listadd_back(t_line **lst, t_line *new);

//		ft_listlast.c
t_line		*ft_listlast(t_line *lst);

//		ft_listnew.c
t_line		*ft_listnew(char *content);

//  ft_split_syn.c
char        **ft_split_syn(char const *s, char c);

//  ft_echo.c
void	ft_echo(t_line *line);

//	parse_line.c
char	*append(char *line, char c);
int		parse_line(char **line, t_list *history);

//	parse_token.c
void	parse_token(char **line, int i);

//	parse_command.c
char	*parse_command(char *line_piece, char *str);

//	main.c
void	split_pipes(char *command_line);

//	exec_pwd.c
char	*exec_pwd(void);
char	*exec_cd(char **command_line);

//	exec_export.c
char	*exec_export(char **command_line, int len);
char	*exec_env(char **command_line, int len);
char	*exec_unset(char **command_line, int len);
int		find_c(char *s, char c);
char	*extract_env(char *str);

//	init.c
int		init_env(char *envp[]);
char	*find_key(const char *str);
char	*find_value(const char *str);

//	util_list.c
// t_env	*ft_listnew(void *key, void *value);
// void	ft_listadd_back(t_env **lst, t_env *new);
// t_env	*ft_listlast(t_env *lst);
// t_env	*ft_listfind(t_env **lst, char *s);

//	other_command.c
char	*other_command(char **command_line, int len);

//	util_str.c
int		is_alpha(char c);
int		is_dollar(char c);
char	*ft_joinfree1(char **s1, char **s2);
char	*ft_joinfree2(char **s1, char **s2);
char	*str_append1(char *s1, char *s2);
char	*str_append2(char *s1, char *s2);
void	free_split(char ***split);
int		ft_strcmp(char *dest, char *src);

#endif
