#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		main(int argc, char **argv, char **envp)
{

	int		pid;
	char	*path;
	char	buf[4096];
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

		path = getcwd(buf, 200);
		printf("current directory : %s\n", path);
		printf("buf %s\n", buf);
		printf("\n");

		chdirn = chdir("/Users/sunmin/proj33t/");
		if (chdirn == 0)
			printf("chdir successed\n");
		else
			printf("chdir failed\n");
		path = getcwd(buf, 200);
		printf("current directory : %s\n", path);
		printf("\n");

		chdirn = chdir("/Users/sunmin/project/cub3d");
		if (chdirn == 0)
			printf("chdir successed\n");
		else
			printf("chdir failed\n");
		path = getcwd(buf, 200);
		printf("current directory : %s\n", path);
		printf("\n");

		chdirn = chdir("../");
		if (chdirn == 0)
			printf("chdir successed\n");
		else
			printf("chdir failed\n");
		path = getcwd(buf, 200);
		printf("current directory : %s\n", path);
		printf("\n");

		chdirn = chdir("~/");
		if (chdirn == 0)
			printf("~/ chdir successed\n");
		else
			printf("~/ chdir failed\n");
		path = getcwd(buf, 200);
		printf("current directory : %s\n", path);
		printf("\n");

		chdirn = chdir("/");
		if (chdirn == 0)
			printf("chdir successed\n");
		else
			printf("chdir failed\n");
		path = getcwd(buf, 200);
		printf("current directory : %s\n", path);
		printf("\n");
	}
	return (0);
}
