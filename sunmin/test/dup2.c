#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int		ft_strlen(char *s);

int		main(int argc, char *argv[], char *envp[])
{
	int		fd1;
	int		fd2;

	fd1 = open("./1.txt", O_RDWR);

	dup2(fd1, 1);
	if (argc == 2)
		write(1, argv[1], ft_strlen(argv[1]));
	if (argc == 3)
		write(fd1, argv[2], ft_strlen(argv[2]));
	return (0);
}

int		ft_strlen(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
