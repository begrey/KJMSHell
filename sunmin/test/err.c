#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

int		main(void)
{
	open("1", O_RDWR);
	
	printf("%d\n", errno);
	errno = 0;
	printf("%d\n", errno);
	return (0);
}

