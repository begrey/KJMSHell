#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char *append(char *line, char c, int flag)
{
	char *str; //이어붙힌 문자열
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

int main(void)
{
	int rd = 0;
	char *line;
	char c;
	int flag = 0; //큰따옴표 1, 작은따옴표 2

	if (!(line = malloc(1)))
		return -1;
	(line)[0] = 0;
	while ((rd = read(0, &c, 1)) > -1)
	{
		if (c == '\"' && flag != 2)
		{
			if (flag == 1)
				flag = 0;
			else
				flag = 1;
		}
		else if (c == '\'' && flag != 1)
		{
			if (flag == 2)
				flag = 0;
			else
				flag = 2;
		}
		else if (c == '\n')
		{
			if (flag == 0)
			{
				write(1, line, ft_strlen(line));
				write(1, "\n", 1);
				return (1);
			}
			else
			{
				line = append(line, '\n', flag);
				write(1, ">", 1);
			}
		}
		else
			line = append(line, c, flag);
	}
	if (rd == -1)
		return (-1);
	return (0);
}
