#include "./MsHell.h"

int		ft_find(char *s, char key)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == key)
			return (1);
		i++;
	}
	return (0);
}
