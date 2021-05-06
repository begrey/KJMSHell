#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				if_value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

t_env *env;

//  ft_echo.c
char	*ft_echo(char *args);

//	parse_line.c
int		ft_strcmp(char *dest, char *src);
char	*append(char *line, char c);
int		parse_line(char **line);

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
t_env	*ft_listnew(void *key, void *value);
void	ft_listadd_back(t_env **lst, t_env *new);
t_env	*ft_listlast(t_env *lst);
t_env	*ft_listfind(t_env **lst, char *s);

//	util_str.c
int		is_alpha(char c);
int		is_dollar(char c);
char	*ft_joinfree1(char **s1, char **s2);
char	*ft_joinfree2(char **s1, char **s2);
char	*str_append1(char *s1, char *s2);
char	*str_append2(char *s1, char *s2);
void	free_split(char ***split);

//	other_command.c
char	*other_command(char **command_line);

//	re_direction.c


#endif
