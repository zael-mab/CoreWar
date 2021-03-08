/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 15:10:31 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/21 15:10:47 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
//  MAX INT FIX IT !!!!
int     check_dir(char *line, int arg, t_node *instr, t_asmdata data)
{
    int x;

    x = ((arg & T_DIR) > 0 ? 1 : 0);
    if (x == 0)
        return (0);
    x = -1;
    while (line[++x])
    {
        if (x == 0 && line[x] == '-')
            x++;
        if (!ft_isdigit(line[x]))
            return(0);
    }
    if (x == 0)
        return (0);
    x = ft_atoi(line);
    ft_printf("DIIIR  x=%d\n",x);
    // if (x > -1)
    instr->arg[data.y] = (ft_atoi(line));
        // instr->arg[data.y] = (ft_atoi(line)) << 8;
    // else
    // {
    //     instr->arg[data.y] = x << 16;
    //     instr->arg[data.y] = (reverse_endian (instr->arg[data.y]));
    // }
    // ft_printf ("\t\t!!!!dir*%d*=[%d]!!!!\n",data.y , instr->arg[data.y]);
    
    return (1);
}



int                check_ind(char *line, int arg, t_head labels)
{
    char *tmp = ft_strtrim (line);
    t_node *l;

    // ft_printf("\t\t\t\t\t\t\t= %s\n", tmp);
    l  = search_by_name(labels.first, tmp);

    if ((arg & T_IND) && l)
    {
        // ft_printf ("!!!Error at arg num[%s]\n", line);
        return (1);
    }
    // if (l)
        // return (1);
    ft_printf ("label not fond [%s]\n", tmp);
    return (0);
}

int         set_label_args(t_head *head, t_head labels, t_asmdata *data)
{
    t_node  *l;
    t_node  *instru;
    int     jumper;
    int     counter;


    instru = head->first;
    l = labels.first;
    counter = 0;
    while (instru)
    {
        if (instru->lb > 0)
        {

            // jumper = -1;
            // while (instru->data[++jumper])
                // if (instru->data[jumper] == ' ')
                    // break ;
            // ft_printf("\t@@@@@%d [[%s\n", ' ' , ft_strrchr(instru->data, 32));
            // data->op_args = ft_strsplit( ft_strrchr(instru->data, 32), SEPARATOR_CHAR);
            jumper = -1;
            while (++jumper < instru->arg_num)
            {
                if ((instru->lb & jumper + 1 && jumper != 2) || (instru->lb & 4 && jumper == 2))
                {
                    if ((l = search_by_name(labels.first, ft_strtrim(1 + ft_strchr(instru->arg_tab[jumper], LABEL_CHAR)))))
                    {
                        ft_printf("[[[[[[[[[[%s]]]]]]]]]]]]]]]], \n", 1 + ft_strchr(instru->arg_tab[jumper], LABEL_CHAR));
                        if (l->size_ind == counter)
                        {
                            instru->arg[jumper] = reverse_endian((counter));
                            // instru->arg[jumper] = counter;
                            ft_printf ("\t\t\t!!!!! %d == %d, %s\n", instru->arg[jumper] , counter, ft_strchr(instru->arg_tab[jumper], LABEL_CHAR));

                        }
                        if (l->size_ind > counter)
                        {
                            instru->arg[jumper] = reverse_endian((l->size_ind - counter) << 16);
                            // instru->arg[jumper] = l->size_ind - counter;
                            ft_printf ("\t\t\t!!!!! %d ||> %d, %s\n", l->size_ind - counter , counter, ft_strchr(instru->arg_tab[jumper], LABEL_CHAR));

                        }
                        if (l->size_ind < counter)
                        {
                            // instr->arg[data.y] = x << 16;
                            // instr->arg[data.y] = (reverse_endian (instr->arg[data.y]));
                            instru->arg[jumper] = reverse_endian((l->size_ind - counter) << 16);
                            ft_printf ("\t\t\t!!!!! %d ||< %d, %s\n",l->size_ind - counter , counter, ft_strchr(instru->arg_tab[jumper], LABEL_CHAR));
                        }

                    }

                    // ft_printf ("!******%s**%s**** ==>%d\n", data->op_args[jumper], 1+ft_strchr(data->op_args[jumper], LABEL_CHAR),head->code_size + instru->command_size);

                }
            }
        }
        counter += instru->command_size;
        ft_memdel((void**) instru->arg_tab);
        data->y = 0;
        instru = instru->next;
    }
    return (1);
}
