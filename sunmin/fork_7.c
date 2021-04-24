#include <unistd.h>

#include <stdio.h>

int		main(void)
{
	pid_t	pid;

	pid = fork();
	printf("%d\n", pid);
	return (0);
}
