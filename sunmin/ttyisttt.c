#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int		main(int argc, char **argv, char **envp)
{
	int		i;
	int		fd[2];

	pipe(fd);
	i = 0;
	while (i < 10)
	{
		printf("%d %d\n", i, isatty(i));
		printf("%s\n", ttyname(i));
		printf("\n");
		i++;
	}
	printf("fd[0] %d\nfd[1] %d\n", isatty(fd[0]), isatty(fd[1]));
	printf("\n");
	printf("current terminal slot number : %d\n", ttyslot());
	printf("\n");
	printf("env / argv[1] = %s\n", getenv(argv[1]));
	return (0);
}
