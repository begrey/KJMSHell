#include "./MsHell.h"

int		ft_find(char *s, char key)
{
	int		i;
	int		num;

	num = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == key)
			num++;
		i++;
	}
	return (num);
}
