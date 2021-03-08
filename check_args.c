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
    instr->arg[data.y] = ft_atoi(line);
    return (1);
}



int                check_ind(char *line, int arg, t_head labels)
{
    char *tmp;
    t_node *l;

    tmp = ft_strtrim (line);
    l  = search_by_name(labels.first, tmp);
    if ((arg & T_IND) && l)
        return (1);
    ft_printf ("Error at arg num[%s]\n", line);
    return (0);
}

int         set_label_args(t_head *head, t_head labels, t_asmdata *data)
{
    t_node  *l;
    t_node  *instru;
    int     counter;

    instru = head->first;
    l = labels.first;
    counter = 0;
    while (instru)
    {
        if (instru->lb > 0)
            get_labels_value(l, instru, labels.first, counter);
        counter += instru->command_size;
        ft_memdel((void**) instru->arg_tab);
        data->y = 0;
        instru = instru->next;
    }
    return (1);
}

/*get the value ready to print  (location counter) */

void        get_labels_value(t_node *l, t_node *instru, t_node *first, int counter)
{
    int jumper;

    jumper = -1;
    while (++jumper < instru->arg_num)
        if ((instru->lb & jumper + 1 && jumper != 2) || (instru->lb & 4 && jumper == 2))
            if ((l = search_by_name(first, ft_strtrim(1 + ft_strchr(instru->arg_tab[jumper], LABEL_CHAR)))))
            {
                if (l->size_ind == counter)
                    instru->arg[jumper] = reverse_endian((counter));
                if (l->size_ind > counter)
                    instru->arg[jumper] = reverse_endian((l->size_ind - counter) << 16);
                if (l->size_ind < counter)
                    instru->arg[jumper] = reverse_endian((l->size_ind - counter) << 16);
            }
}