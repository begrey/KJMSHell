#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>


int		main(int argc, char **argv, char **envp)
{
	int		fd1;
	int		fd2;
	char	buf[1000];

	fd1 = open("./test.txt", O_RDONLY);
	printf("fd1 : %d\n", fd1);
	read(fd1, buf, 2);
	printf("read 2bytes : %s\n", buf);
	fd2 = dup(fd1);							// dup로 fd를 받아오면 공유됨
	printf("fd2 : %d\n", fd2);				// 커널의 같은 파일 엔트리를 참고한다
	read(fd2, buf, 2);
	printf("read 2bytes : %s\n", buf);
	read(fd1, buf, 2);
	printf("read 2bytes : %s\n", buf);

	int		fd3;
	fd3 = dup2(fd2, 100);			// 이런 식이라면  그냥 fd3 = 100;이랑 뭐가 다른지
	printf("fd3 : %d\n", fd3);
	read(99, buf, 2);
	printf("read 2bytes : %s\n", buf);
	return (0);
}
