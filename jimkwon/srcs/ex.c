#include <termcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char buf[255];
	int ret;

	write(0, "\033[6n", 4);
	ret = read(0, buf, 254);
	buf[ret] = 0;
	write(0, buf, 254);
}
