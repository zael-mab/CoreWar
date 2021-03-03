/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:06:16 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/27 19:06:25 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// first 4 bytes COREWAR_EXEC_MAGIC 0xea83f3
// Each character is written to the file as it's ASCII value
//  the name take 128  PROG_NAME_LENGTH eache convert each caracter (dec)to(hexa)
// 4 bytes for NULL 
// champion exic code size 4 bytes.
// champion comment 2048 bytes COMMENT_LENGTH
// 4 bytes for NULL
// the last part of the file is executaple code (no trailling zeros in this part)
// to convert we will need 
//          *the size of T_DIR (2 or 4)

// Operation:
// 1 byte[Operation code]  | 1 byte[encodinng byte]*  | 1 byte [arg_1]  | 2 bytes[arg_2]  |  2 bytes[arg_3]
//      **The code for each operation can be found in the operations table 0-16.
//      ***the encoding byte
//             -reg[01] , dir[10], ind[11] =>[01101000]
//            +reg ==> convert the number x (rx)    [r1]=>[0x01].
//            +dit ==> 

char	*it_base(unsigned long long vl, int base);

void        decode(t_asmdata *data)
{
    int fd;
    // int str = COREWAR_EXEC_MAGIC;
    // int i = sizeof (COREWAR_EXEC_MAGIC);
    FILE *fp;
    fp = fopen("file.txt","wb+");
    fd = open ("z.cor", O_CREAT | O_APPEND | O_RDWR, 0600, "wb+");
    if (fd < 0)
    {
        perror ("open");
        exit(1);
    }
    // while (++i < 8)
    // {
    //     int j = 3;
    //     while (--j)
        // write (fd, &arr[i], 1);
        fprintf(fp, "%i", COREWAR_EXEC_MAGIC);
        ft_printf("%x\n", COREWAR_EXEC_MAGIC);
    //     i--;
    //     lseek(fd, i*sizeof (str), SEEK_END);
    //     str++;
    // }
    ft_printf("%s\n", data->name);

    char *t = it_base((unsigned long long)COREWAR_EXEC_MAGIC, 0);
    ft_printf ("%s\n", t);
    // while (*data->name)
    // {
        // write(fd, &data->name)
    // }
    close (fd);
}

char	*it_base(unsigned long long vl, int base)
{
	int x;
    char *arr;
    unsigned long long i;

	i = vl;
	x = 1;
	while ((i = i / base) >= 1)
		x++;
	arr = ft_strnew(x);
	i = (vl > 0 ? vl : -vl);
	while (x--)
	{
		if (i % base < 10)
			arr[x] = i % base + '0';
		else
			arr[x] = i % base + 'a' - 10;
		i = i / base;
	}
	arr[x] = ((x == 0) ? '-' : '0');
    return (arr);
}
