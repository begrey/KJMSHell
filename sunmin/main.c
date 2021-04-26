/*

* Objective of this file*

To make a program that uses all of functions allowed, to be accustomed to them.

*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		main(void)
{

	int		pid;
	char	*path;
	char	*buf;
	int		chdirn;

	pid = fork();


	if (pid == 0)
	{
		printf("%d : I'm son\n", pid);
		printf("\n");
	}
	else
	{
		printf("%d : I'm your father\n", pid);
		printf("\n");

		path = getcwd(buf, 1);
		printf("current directory : %s\n", path);
		printf("buf %s\n", buf);
		printf("\n");

		chdirn = chdir("/Users/sunmin/proj33t/");
		if (chdirn == 0)
			printf("chdir successed\n");
		else
			printf("chdir failed\n");
		path = getcwd(buf, 70);
		printf("current directory : %s\n", path);
		printf("\n");

		chdirn = chdir("/Users/sunmin/project/cub3d");
		if (chdirn == 0)
			printf("chdir successed\n");
		else
			printf("chdir failed\n");
		path = getcwd(buf, 20);
		printf("current directory : %s\n", path);
		printf("\n");

		chdirn = chdir("../");
		if (chdirn == 0)
			printf("chdir successed\n");
		else
			printf("chdir failed\n");
		path = getcwd(buf, 20);
		printf("current directory : %s\n", path);
		printf("\n");

		chdirn = chdir("~/");
		if (chdirn == 0)
			printf("~/ chdir successed\n");
		else
			printf("~/ chdir failed\n");
		path = getcwd(buf, 20);
		printf("current directory : %s\n", path);
		printf("\n");

		chdirn = chdir("/");
		if (chdirn == 0)
			printf("chdir successed\n");
		else
			printf("chdir failed\n");
		path = getcwd(buf, 20);
		printf("current directory : %s\n", path);
		printf("\n");

		free(path);
	}
	return (0);
}
