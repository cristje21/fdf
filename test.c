#include <unistd.h>
#include <stdio.h>
#include <sys/errno.h>

int	main(void)
{
	printf("%d\n", errno);
	return (0);
}
