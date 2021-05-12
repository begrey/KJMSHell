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

void	get_cursor_position(int *col, int *rows)
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
				*rows = atoi(&buf[i]) - 1;
			else
			{
				temp = atoi(&buf[i]) - 1;
				*col = temp - 1;
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

void	move_cursor_left(int *col, int *row, char *cm)
{
	if (*col == 0)
		return ;
	(*col) -= 1;
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);

}

void	move_cursor_right(int *col, int *row, char *cm)
{
	++(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);

}

void	delete_end(int *col, int *row, char *cm, char *ce)
{
	if (*col != 0)
		--(*col);
	tputs(tgoto(cm, *col, *row), 1, putchar_tc);
	tputs(ce, 1, putchar_tc);
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
	char *cm = tgetstr("cm", NULL); //cursor motion
	char *ce = tgetstr("ce", NULL); //clear line from cursor
	
	int c;
	int row;
	int col;
	char ch;

	c = 0;
	if (!(*line = malloc(1)))
		return (-1);
	(*line)[0] = 0;
	while (read(0, &c, sizeof(c)) > 0)
	{
		get_cursor_position(&col, &row);
		if (c == L_ARROW)
			move_cursor_left(&col, &row, cm);
		else if (c == R_ARROW)
			move_cursor_right(&col, &row, cm);
		else if (c == U_ARROW)
			printf("UP_ARROW\n");
		else if (c == D_ARROW)
			printf("DOWN_ARROW\n");
		else if (c == BACKSPACE)
			delete_end(&col, &row, cm, ce);
		else
		{
			col++;
			ch = (char)c;
			write(1, &ch, 1);
			if (ch == '\n')
				return (1);
			*line = append(*line, ch);
			if (!*line)
				return (0);
		}
		c = 0; //flush buffer
	}
	return (-1);
}
