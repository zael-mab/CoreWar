/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lseek.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 15:19:21 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/01 17:52:32 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>

int main (int ac, char **av)
{
	int fd = open("x.cor", O_CREAT | O_APPEND | O_RDWR, 0600);
	int r;
//	char str[8] = {0, 1, 2, 3, 4, 5, 6, 7};
	int b;
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}

	int i;
	i = -1;
	char x = 0;
	while (av[1][++i])
	{
		x +=i;
		r = write (fd, &x, 1);
	}
	if (fd < 0)
	{
		perror("write");
		close (fd);
		exit(1);
	}
	return (0);
//	r = lseek (fd, 10*sizeof (char), SEEK_END);
	
	if (fd < 0)
	{
		perror ("lseek");
		close (fd);
		exit(1);
	}

	r = read (fd, &b, sizeof (int));
	printf ("b=%d\n", b);

	close (fd);
	return (0);
}
