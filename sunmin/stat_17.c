#include <sys/stat.h>

int		main(void)
{
	struct stat		*buf;
	stat("./1.c", buf);
	return (1);
}
