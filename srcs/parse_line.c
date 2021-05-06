#include "minishell.h"

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
