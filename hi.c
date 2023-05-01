#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int fd;

	fd = open("text", O_RDONLY | O_WRONLY);
	dup2(fd, 1);
	close(fd);
	printf("Ewaa Olee\n");
	return (0);
}
