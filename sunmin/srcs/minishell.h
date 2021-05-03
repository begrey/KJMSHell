/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:38:51 by jimkwon           #+#    #+#             */
/*   Updated: 2021/05/03 11:00:49 by sunmin           ###   ########.fr       */
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
# include "../libft/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	int				if_value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

t_env *env;		// 리스트 구조체를 key, value, prev 등 수정해야 하고 리스트 함수도 다시 만들어야 함


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

#endif
