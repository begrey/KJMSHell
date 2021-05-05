/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimkwon <jimkwon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 10:38:51 by jimkwon           #+#    #+#             */
/*   Updated: 2021/05/05 12:30:59 by sunmin           ###   ########.fr       */
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

//  ft_split_syn.c
char        **ft_split_syn(char const *s, char c);

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

//	other_command.c
char	*other_command(char **command_line, int len);

#endif
