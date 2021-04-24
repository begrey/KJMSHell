#include <unistd.h>

#include <stdio.h>

int		main(void)
{
	pid_t	son;
	pid_t	daughter;

	son = fork();
	daughter = fork();
	printf("abcde\n");;
	return (0);
}
