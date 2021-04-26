#include <stdio.h>
#include <unistd.h>

int		main(void)
{
	unsigned long	a = 11412272606825;
	write(1, &a, 6);
	return (0);
}
