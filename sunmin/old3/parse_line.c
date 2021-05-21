#include "minishell.h"

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

int parse_line(char **line)
{
	int rb;
	char buff;
	if (!(*line = malloc(1)))
	return (-1);
	(*line)[0] = 0;
	while ((rb = read(0, &buff, 1) > 0))
	{
		if (buff == '\n')
		return (1);
		*line = append(*line, buff);
		if (!*line)
		return (0);
	}
	if (rb == -1)
	return (-1);
	return (0);
}
