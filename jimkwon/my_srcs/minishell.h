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
}				t_cursor;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				if_value;
	struct s_env	*prev;
	struct s_env	*next;
}				t_env;

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

//	ft_echo.c
void		ft_echo(t_line *line);

//	ft_cd.c
void		ft_cd(t_line *line);
char		*convert_root_path(t_line *line);
char		*root_path();

//	ft_pwd.c
void		ft_pwd(t_line *line);

//	test_pip.c
void exec_command(char *command, int pipefd[2], int flags);
void pipe_exec(t_pipe *pip, t_line *list);
		//main.c 바꿀것

// //	exec_command.c
// void		exec_command(t_line *line);

//	other_command.c
char	*other_command(char **command_line, int len);

//	parse_line.c    후에 히스토리랑 커서 별로 바꾸자
int		num_len(int n);
int		putchar_tc(int tc);
void	get_cursor_position(t_cursor *cursor);
void	delete_end(t_cursor *cursor);
void	delete_line(t_cursor *cursor);
char	*remove_c(char *line);
char	*append(char *line, char c);
void	renew_history(t_list **history, char *line, int cnt);
int		find_history(t_list *history, char **line, int cnt, t_cursor *cursor);
int		parse_line(char **line, t_list *history);

//	ft_add_back.c
void		ft_pipeadd_back(t_pipe **pip, t_pipe *new);


//	ft_last.c
t_pipe		*ft_pipelast(t_pipe *lst);


//	ft_new.c
t_pipe		*ft_pipenew(int *pipe);















































#endif
