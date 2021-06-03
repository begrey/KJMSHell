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
# define STDIN_PIPE 0x1
# define STDOUT_PIPE 0x2
# define READ 0
# define WRITE 1

typedef struct	s_cursor
{
	char			*cm; //cursor motion
	char			*ce; //cursor erase
	char			*prev_his; // 이전 명령어
	int				row;
	int				col;
	int				prev_col; //col 마지막 칸 두개는 한칸취급당하기 떄문에
	int				last_col_flag; // 마지막 칸이라는 플래그
	int				max_col;
}				t_cursor;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				if_value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

char	*g_line;

typedef	struct	s_redirc
{
	int				type;
	char			*f_name;

}				t_redirc;		

typedef struct		s_pipe
{
	int				fd[2]; //pipe용 fd
	struct s_pipe	*next;
}					t_pipe;	

typedef struct s_line
{
	char				*arg;
	struct s_line		*prev;
	struct s_line		*next;
}				t_line;

//  signal.c

void		signal_sigquit(int sig);
void		signal_handler(int sig);
void		set_signal_return(t_env *env);
void		init_g_line(void);
void		init(t_env **env, char **list, t_list **history);

//	ft_echo.c
void		ft_echo(t_line *line, int pip_flag, t_env *env);

//	ft_cd.c
void		ft_cd(t_line *line, t_env *env, int pip_flag);
char		*convert_root_path(t_line *line, t_env *env);
char		*root_path(t_env *env);

//	ft_pwd.c
void		ft_pwd(int pip_flag, t_env *env);

//	pipe.c
void		dup_pipe(t_line *list, int pipefd[2], int flags, t_env *env);
int			pipe_exec(t_pipe *pip, t_line **list, t_env *env);
void		split_by_pipe(t_line *list, t_env *env);

//	exec_command.c
void		exec_command(t_line *line, char *file_name, t_env *env, int pip_flag);

//	other_command.c
void		other_command(t_line *line, t_env *env, char *file_name, int pip_flag);
void		other_command_exec(t_line *line, t_env *env, char *file_name);

//	input_line.c    후에 히스토리랑 커서 별로 바꾸자
int			remove_c(t_cursor *cursor);
int			append(char c);
int					put_cursor(t_cursor *cursor, struct termios term, char c);
int				check_c(t_list *history, int *h_cnt, t_cursor *cursor, int c);
int			input_line(t_list *history, t_env *env, int c);

//	cursor.c
int			putchar_tc(int tc);
void		set_cursor_row_col(t_cursor *cursor, char *buf);
void		get_cursor_position(t_cursor *cursor);
void		delete_end(t_cursor *cursor);
void		delete_line(t_cursor *cursor);

//  history.c
void		renew_history(t_list *history, int cnt);
int			adjust_cnt(t_list *history, int cnt, t_cursor *cursor);
int			find_history(t_list *history, int cnt, t_cursor *cursor);

//	term.c
void				init_cursor_term(t_cursor *cursor,
struct termios *term, int *h_cnt);
struct termios		term_on();
void		term_off();
int			num_len(int n); 
void				set_sigint_env(t_env *env);

//	util_pipe.c
t_pipe		*ft_pipenew();
t_pipe		*ft_pipelast(t_pipe *lst);
void		ft_pipeadd_back(t_pipe **pip, t_pipe *new);
int			ft_pipesize(t_line *list);

//ft_export.c
void	exec_export(t_line *line, t_env *env, int pip_flag);
void	exec_env(t_line *line, t_env *env, int pip_flag);
void	exec_unset(t_line *line, t_env *env, int pip_flag);

//ft_export_util.c
char	*extract_env(char *str, t_env *env);
void	if_value_or_not(t_line **tmp, int *if_value, char **value, t_env *env);
void	make_if_value_export(t_env *env, char *ex_env, char *value);
void	make_no_value_export(char *ex_env, t_env *env);
void	put_if_value_export(t_env *temp, char *value);
//ft_export_util2.c
void	printf_export(t_env *env);
int		is_alpha_dollar_str(char *s);

// sunmin 추가


//		util_list.c
void		ft_listadd_back(t_line **lst, t_line *new);
t_line		*ft_listlast(t_line *lst);
t_line		*ft_listnew(char *content);
int			ft_listsize(t_line *line);

//		util_envlist.c
t_env		*ft_envnew(void *key, void *value, int if_value);
void		ft_envadd_back(t_env **lst, t_env *new);
t_env		*ft_envfind(t_env **lst, char *s);
t_env		*ft_envlast(t_env *lst);

//		util_envlist2.c
char		*find_key(const char *str);
char		*find_value(const char *str);
void		put_return(int ret, t_env *env);
int			return_return(t_env *env);

//		init_env.c
t_env		*init_env(char *envp[], t_env *env);

//		ft_split_quote.c
char		**ft_split_quote(char *str, char **split, char flag);
int			is_space(const char c);		//  나중에 util로 빼기
char		flag_check(const char c, char flag); // util
int			is_quote(const char c);		// util로 빼기
void	free_split(char **split);

//		convert_env.c
char		*convert_env(const char *str, t_env *env);
void		join_env_temp(char *s, char **result, t_env *env);
int			get_new_len(const char *str, t_env *env);
int			if_effective(const char *str, int flag);
char		*exact_envstr(char *str);
//		convert_env_util.c
int			check_flag(char c, int flag);
int			check_env_len(const char *str);
char		*put_return_value(char *res);
//		convert_env_util2.c
char		*ft_append(char *s, char c);
int			free_temp(char *s, t_env *env);
int			if_env_dollar(char c1, char c2);

//		redir_syn_check.c
int			redir_syn_check(t_line *line);

//		split_by_null.c
void		split_by_semi(t_line *line, t_env *env);
t_line		*ft_list_null_term(t_line *lst, int index);
int			ft_split_list_token(t_line *lst, char token);

//		redirection.c
void		ft_redirection(t_line *line, t_env *env, int pip_flag, int *fd);
int			which_redir(char *s);

//		token_syn_check.c
int			token_syn_check(t_line *line);

//		parse.c
int			is_token(char *s);
int			make_list(t_env *env);
//		parse_util.c
char	*put_bytes(char **split_token, char *s, int i);
void	list_split_addback(t_line **lst, char *arg);
char	**ft_token_split(char *arg);
char	*put_token_byte(char **split_token, char *s, int i, char c);
char	*put_token_bytes(char **split_token, char *s, int i);

//		parse_util2.c
int		ft_strerror(char *s);
int		is_token(char *s);
int		is_token_quote(const char *str);
int		where_token(char *str);

//		util_str.c
int			ft_strcmp(char *dest, char *src);
char		*str_append1(char *s1, char *s2);
char		*str_append2(char *s1, char *s2);
char		*str_append3(char *s1, char c);
int			is_alpha(char c);
int			is_dollar(char c);
char	*str_appendchar(char *s1, char c);

//		ft_env_sort.c
void		ft_env_sort(t_env **env);

//		convert_escape.c
char		*delete_escape(char *s);
char		*restore_escape(char *s);
char		*convert_escape(char *s);
//		convert_escape_util.c
void		init_var(int *i, int *flag);

//		exit.c
void		ft_exit(t_line *line, t_env *env, int pip_flag);

void		free_struct(t_line *list);
void		free_list_struct(t_line **list);
void		free_pipe(t_pipe *list);

//		ft_env.c
void	exec_env(t_line *line, t_env *env, int pip_flag);
void	pip_exit(int pip_flag);
void	print_env(t_env *idx);
//		ft_unset.c
void	exec_unset(t_line *line, t_env *env, int pip_flag);
void	free_single_env(t_env *env);

#endif


