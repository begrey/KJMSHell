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
	char	buf[255];
	int		ret;
	int		temp;

	a = 0;
	i = 1;
	write(0, "\033[6n", 4);  //report cursor location
	ret = read(0, buf, 254);
	buf[ret] = '\0';
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			if (a == 0)
				cursor->row = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]) - 1;
				cursor->col = temp - 1;
			}
			a++;
			i += num_len(temp) - 1;
		}
		i++;
	}
}

int		putchar_tc(int tc)
{
	write(1, &tc, 1);
	return (0);
}

void	move_cursor_left(t_cursor *cursor)
{
	if (cursor->col == 17)
		return ;
	(cursor->col) -= 1;
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);

}

void	move_cursor_right(t_cursor *cursor)
{
	++(cursor->col);
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
	//printf("why?\n");
}

void	delete_end(t_cursor *cursor)
{
	if (cursor->col != 0)
		--(cursor->col);
	tputs(tgoto(cursor->cm, cursor->col, cursor->row), 1, putchar_tc);
	tputs(cursor->ce, 1, putchar_tc);
}

int ft_strcmp(char *dest, char *src) {
	int i = 0;
	while (dest[i] != '\0' || src[i] != '\0') {
		if (dest[i] > src[i])
			return dest[i] - src[i];
		else if (dest[i] < src[i])
			return dest[i] - src[i];
		i++;
	}
	return 0;      
}

char *append(char *line, char c)
{
	char *str; //이어붙인 문자열
	int i;

	i = 0;
	if(!(str = (char *)malloc(sizeof(char) * (ft_strlen(line) + 2))))
			return NULL;
	while(line[i] != '\0')
	{
		str[i] = line[i];
		i++;
	}
	str[i] = c;
	i++;
	str[i] = 0;
	free(line);
	return (str);
}

void delete_line(t_cursor *cursor)
{
	int len;

	get_cursor_position(cursor);
	len = cursor->col - 19;
	//cursor->col =  cursor->col - len + 1;
	if (cursor->col < 0)
		cursor->col = 0;
	tputs(tgoto(cursor->cm, cursor->col - len, cursor->row), 1, putchar_tc);
	tputs(cursor->ce, 1, putchar_tc);
}

int find_history(t_list *history, char **line, int cnt, t_cursor *cursor)
{
	t_list	*temp;
	int		len;
	int		i;

	if (cnt <= 0)
		cnt = 1; // down_arrow 최소값 조정
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
	// if (temp == NULL)
	// {
	// 	write(1, "NULL", 4);
	// 	return (i);
	// }
	delete_line(cursor);
	write(1, temp->content, ft_strlen(temp->content));
	cursor->prev_his = temp->content;
	*line = temp->content;
	return (cnt);
}

int parse_line(char **line, t_list *history)
{
// 터미널 세팅 설정 
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ICANON;
	term.c_lflag &= ~ECHO;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);

	// termcap 초기화 
	tgetent(NULL, "xterm");
	t_cursor cursor;

	cursor.cm = tgetstr("cm", NULL); //cursor motion
	cursor.ce = tgetstr("ce", NULL); //clear line from cursor
	cursor.prev_his = 0;
	
	int c;
	char ch;
	int h_cnt; //history count

	c = 0;
	h_cnt = 0;
	if (!(*line = malloc(1)))
		return (-1);
	(*line)[0] = 0;
	get_cursor_position(&cursor);
	//col += 5;
	while (read(0, &c, sizeof(c)) > 0)
	{
		//printf("%d\n", h_cnt);
		// if (c == L_ARROW)
		// 	move_cursor_left(&col, &row, cm);
		// else if (c == R_ARROW)
		// 	move_cursor_right(&col, &row, cm);
		if (c == U_ARROW)
			h_cnt = find_history(history, line, h_cnt + 1, &cursor);
		else if (c == D_ARROW)
			h_cnt = find_history(history, line, h_cnt - 1, &cursor);
		else if (c == BACKSPACE)
			delete_end(&cursor);
		else
		{
			cursor.col++;
			ch = (char)c;
			write(1, &ch, 1);
			if (ch == '\n')
				return (1);
			*line = append(*line, ch);
			if (!*line)
				return (0);
		}
		c = 0; //flush buffer
		get_cursor_position(&cursor);
	}
	return (-1);
}
