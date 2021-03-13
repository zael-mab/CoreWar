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
/*
first 4 bytes COREWAR_EXEC_MAGIC 0xea83f3
Each character is written to the file as it's ASCII value
 the name take 128  PROG_NAME_LENGTH eache convert each caracter (dec)to(hexa)
4 bytes for NULL 
champion exic code size 4 bytes.
champion comment 2048 bytes COMMENT_LENGTH
4 bytes for NULL
the last part of the file is executaple code (no trailling zeros in this part)
to convert we will need 
         *the size of T_DIR (2 or 4)

Operation:
1 byte[Operation code]  | 1 byte[encodinng byte]*  | 1 byte [arg_1]  | 2 bytes[arg_2]  |  2 bytes[arg_3]
     **The code for each operation can be found in the operations table 0-16.
     ***the encoding byte
            -reg[01] , dir[10], ind[11] =>[01101000]
           +reg ==> convert the number x (rx)    [r1]=>[0x01].
           +dit ==> 
*/

void        writ_args(t_asmdata *data, t_node *cmd, int fd)
{
    data->x = -1;
    while (++data->x < cmd->arg_num)
    {
        if (!(cmd->w_args[data->x] & T_LAB))
        {
            if (cmd->w_args[data->x + 6] == 2)
            {
                cmd->arg[data->x] = reverse_endian(cmd->arg[data->x] << 16);
                write (fd, &cmd->arg[data->x], cmd->w_args[data->x + 6]);
            }
            else if (cmd->w_args[data->x + 6] == 4)
            {
                cmd->arg[data->x] = reverse_endian(cmd->arg[data->x]);
                write (fd, &cmd->arg[data->x], cmd->w_args[data->x + 6]);
            }
            else
                write (fd, &cmd->arg[data->x], cmd->w_args[data->x + 6]);
        }
        else
            write (fd, &cmd->arg[data->x], cmd->w_args[data->x + 6]);
    }
}

void        decode(t_asmdata *data, t_head *cmmnd, int fd)
{
    t_node  *cmd;

    cmd = cmmnd->first;
    while (cmd)
    {
        if (cmd->code > 0)
        {
            write (fd, &cmd->code, 1);
            if (cmd->encodin_code > 0)
                write (fd, &cmd->encodin, 1);
            writ_args(data, cmd, fd);
        }
        ft_memdel((void **)cmd->arg_tab);
        cmd = cmd->next;
    }
}

// norme
void    to_byte_code(t_head *head, t_asmdata *data)
{		
    int fp;
    int jumper;
    long int c;

    fp = open (data->file_name, O_CREAT | O_RDWR, 0600);					//CHANGE THE NAME OF THE FILE !!!
    jumper = -1;
    
    int y = reverse_endian(COREWAR_EXEC_MAGIC);
    write (fp, &y, 4);												// revers the magic_code and print it as a hex

    jumper = -1;
    while (data->name[++jumper] && write (fp, &data->name[jumper], 1));	// print the name

    c = PROG_NAME_LENGTH - ft_strlen(data->name) + 4;
    lseek(fp, c * sizeof (char), SEEK_END);

    y = reverse_endian(head->code_size);							// revers the code_size and print it.
    write(fp, &y, 4);

    jumper = -1;
    while (data->comment[++jumper] && write (fp, &data->comment[jumper], 1));	// print the comment
    c = COMMENT_LENGTH - ft_strlen(data->comment) + 4;
    lseek(fp, c * sizeof (char), SEEK_END);
    
    if (head->first == NULL || fp < 0)
        exit(0);
    
    decode(data, head, fp);
    ft_printf("Succes Writing output program to %s\n", data->file_name);        // be sure to free the structers !!!
    free (data->file_name);
    close (fp);
}



////////////////////////////////////////////////////
