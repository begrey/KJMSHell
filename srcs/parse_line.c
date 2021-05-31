#include "minishell.h"

int	num_len(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	get_cursor_position(t_cursor *cursor)
{
	int		a;
	int		i;
	char	*buf;
	int		ret;
	int		temp;

	a = 0;
	i = 1;
	buf = NULL;
	buf = (char *)malloc(sizeof(char) * 255);
	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	int fd = open("./a", O_RDWR | O_CREAT | O_APPEND, 00777);
	write(fd, buf, ret);
	while (*buf)
	{
		if (*buf >= '0' && *buf <= '9')
		{
			if (a == 0)
			{
				cursor->row = atoi(buf) - 1;
				write(fd, "\nrow ", 5);
				write(fd, buf, 2);
				write(fd, ", ", 2);
				buf += num_len(cursor->row);
			}
			else
			{
				 write(fd, "col ", 4);
				temp = atoi(buf) - 1;
				cursor->col = temp;
				write(fd, buf, 2);
				//char c = cursor->first_row + 'A';
				//write(fd, &c, 1);
				return ;
			}
			a++;
		}
		buf++;
	}
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	delete_end(t_cursor *cursor)
{

	get_cursor_position(cursor);
	if ((int)ft_strlen(g_line) == 0)
	{
		delete_line(cursor);
		return ;
	}
	cursor->prev_col = cursor->col; //맨 마지막 col 2개는 같은 좌표 취급 당해서!
	--(cursor->col);
	if (cursor->col == -1) //한번 다음줄로 넘어갔다는 소리니까 next_flag on
	{
		cursor->row--;
		cursor->col = cursor->max_col - 1;
	}
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
	tputs(cursor->ce, 1, putchar_tc);
}
int		remove_c()
{
	char *str; //끝 문자 제거할 문자열
	int i;

	i = 0;
	if (ft_strlen(g_line) == 0)
	{
		g_line[0] = 0;
		return (0);
	}
	if(!(str = (char *)malloc(sizeof(char) * ft_strlen(g_line))))
			return (-1);
	while(i != (int)ft_strlen(g_line) - 1)
	{
		str[i] = g_line[i];
		i++;
	}
	str[i] = 0;
	//free(g_line);
	g_line = str;
	return (0);
}

int		append(char c)
{
	char *str; //이어붙일 문자열
	int i;

	i = 0;
	if(!(str = (char *)malloc(sizeof(char) * (ft_strlen(g_line) + 2))))
			return (-1);
	while(g_line[i] != '\0')
	{
		str[i] = g_line[i];
		i++;
	}
	str[i] = c;
	i++;
	str[i] = 0;
	//free(g_line);
	g_line = str;
	return (0);
}

void delete_line(t_cursor *cursor)
{
	int len;

	get_cursor_position(cursor);
	len = cursor->col - 19;   //-19
	if (cursor->col < 0)
		cursor->col = 0;
	tputs(tgoto(cursor->cm, cursor->col - len, cursor->row), 1, putchar_tc);
	tputs(cursor->ce, 1, putchar_tc);
}

void	renew_history(t_list *history, int cnt) //히스토리 갱신
{
	t_list	*temp;
	int		len;
	int		i;

	if (history == NULL || cnt <= 0)
		return ;
	temp = history;
	i = 1;
	len = ft_lstsize(history) - cnt + 1;
	while (temp != NULL && i != len)
	{
		temp = temp->next;
		i++;
	}
	temp->content = g_line;
}

int find_history(t_list *history, int cnt, t_cursor *cursor)
{
	t_list	*temp;
	int		len;
	int		i;

	if (history == NULL)
		return (0);
	if (cnt <= 0)
	{
		delete_line(cursor);
		g_line = ft_strdup("");
		return (0); // down_arrow 최소값 조정
	}
	else if (cnt >= ft_lstsize(history)) // up_arrow가 기존 히스토리 길이보다 큰 경우 최대값으로 조정
		cnt = ft_lstsize(history);
	temp = history;
	i = 1;
	len = ft_lstsize(history) - cnt + 1; // 맨 뒤부터 첫번쨰, cnt가 2고 사이즈가 5면 4번째 출력
	while (temp != NULL && i != len)
	{
		temp = temp->next;
		i++;
	}
	delete_line(cursor);
	write(1, temp->content, ft_strlen(temp->content));
	cursor->prev_his = temp->content;
	g_line = temp->content;
	return (cnt);
}

void term_off(struct termios term)
{
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

}

struct termios term_on()
{
	// 터미널 세팅 설정 
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	return (term);
}

int parse_line(t_list *history, t_env *env)
{
	struct termios term;
	term = term_on();
	t_cursor cursor;

		// termcap 초기화 
	tgetent(NULL, "xterm");
	cursor.cm = tgetstr("cm", NULL); //cursor motion
	cursor.ce = tgetstr("ce", NULL); //clear line from cursor
	
	int c;
	int h_cnt; //history count

	c = 0;
	h_cnt = 0;
	//cursor.col++;
	get_cursor_position(&cursor);
	cursor.max_col = 0;
	cursor.prev_col = 0;
	//printf("%d", cursor.first_row);
	while (read(0, &c, sizeof(c)) > 0)
	{
		if (g_line[0] == -3)
		{
			put_return(1, env);
			g_line[0] = 0;
		}
		if (c == U_ARROW)
		{
			h_cnt = find_history(history, h_cnt + 1, &cursor);
		}
		else if (c == D_ARROW)
		{
			h_cnt = find_history(history, h_cnt - 1, &cursor);
		}
		else if (c == BACKSPACE)
		{ 
			if((remove_c()) == -1)
				return (0);
			delete_end(&cursor);
		}
		else if (c != L_ARROW && c != R_ARROW)
		{
			write(1, &c, 1);
			get_cursor_position(&cursor);
			if (cursor.max_col <= cursor.col)
				cursor.max_col = cursor.col;
			//if (c != -1) //그냥 넘겨버릴 땐 append 안해야 line에 값 안붙음
			if ((append((char)c)) == -1)
				return (0);
			if ((char)c == '\n')
			{
				term_off(term);
				return (1);
			}
			if (!g_line)
				return (0);
			renew_history(history, h_cnt);
		}
		if (c == 4)
		{
			if ((int)g_line[0] == 4)
				return (-1); //ctrl-d
		}
		c = 0; //flush buffer
	}
	return (-1);
}
