#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

int		ft_strlen(char *s);

int		main(int argc, char *argv[], char *envp[])
{
	pid_t	pid1;
	int		*status;
	int		fd1;

	fd1 = 1;
		if (argc >= 3)
		{
			fd1 = open (argv[2], O_RDWR | O_CREAT | O_TRUNC | O_APPEND, 00777);
			dup2(fd1, 1);
		}
		write(fd1, argv[1], ft_strlen(argv[1]));
		write(fd1, "\n", 1);
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
