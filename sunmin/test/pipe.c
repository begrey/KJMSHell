#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1


int				main(int argc, char **argv)
{
	int			*pip;
	int			fd;
	int			stat;
	pid_t		pid;
	char		buf[1024];
	int			*status;

	pip = (int *)malloc(sizeof(int) * 2);
	fd = open("./ex.txt", O_RDWR | O_CREAT | O_TRUNC, 00777);
	stat = pipe(pip);

	pid = fork();
	if (pid)		// 부모
	{
		close(1);		// pip[write]
		read(0, buf, 1024);	// pip[read]
		wait(status);
		printf("parents got message: %s", buf);
	}
	else			// 자식
	{
		close(0);		//pip[read]
		strcpy(buf, "message from child\n");
		write(1, buf, strlen(buf));		//pip[write]
	}

	dup2();
	printf("asdf\n");		//1
	return (0);
}
