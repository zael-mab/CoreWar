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

// void        convert_nameacom(t_asmdata *data, int fd)
// {
//     char t;

//     fd = open ("z.cor", O_CREAT | O_APPEND | O_RDWR, 0600);
//     while ()
//     while (*data->name)
// }