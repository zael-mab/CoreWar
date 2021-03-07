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


void        decode(t_asmdata *data, t_head *cmmnd, int fd)
{
    t_node *cmd;

    if (cmmnd->first == NULL || fd < 0)
        exit(0);
    cmd = cmmnd->first;
    while (cmd)
    {
        if (cmd->code > 0)
        {
            // ft_printf("\t\t====%s=====\n", cmd->data);

            write (fd, &cmd->code, 1);
            if (cmd->encodin_code > 0)
                write (fd, &cmd->encodin,1);
            data->x = -1;
            while (++data->x < cmd->arg_num)
            {
                // if (cmd->arg[data->x] & T_REG)
                // {
                // ft_printf ("####%d- %d-####\n", cmd->arg[data->x], cmd->w_args[data->x + 6]);
                write (fd, &cmd->arg[data->x], cmd->w_args[data->x + 6]);

                // }

            }
            // lseek(fd, sizeof (char), SEEK_END);
        }
        cmd = cmd->next;
    }
    ft_printf ("%d\n", data->error);
}



// // 0b68 0100 0700 0101 0000 0000 0290 0000
// 0000 0209 ffed
