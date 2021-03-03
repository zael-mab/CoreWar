#include "asm.h"

int main (int ac, char **av)
{
	int fd;

	fd = open ("ex.cor", O_CREAT | O_RDWR, 0600);
	int i = 32;
	char t[2];
	t[0]= 0;
	t[1] = (char )i; 
	write (fd, &t[0], 1);
	write (fd, &t[1], 1);
	close (fd);
}
