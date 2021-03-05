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
    instr->arg[data.y] = ft_atoi(line);
    
    // ft_printf ("\t\t!!!!dir=%d!!!!\n", instr->arg[data.y]);
    
    return (1);
}



int                check_ind(char *line, int arg, t_head labels)
{
    char *tmp = ft_strtrim (line);
    t_node *l;

    ft_printf("= %s\n", tmp);
    l  = search(labels.first, tmp);

    if (!(arg & T_IND))
    {
        ft_printf ("!!!Error at arg num[%s]\n", line);
        return (0);
    }
    if (l)
    {
        // ft_printf ("\t \tlable === %s\n", l->data);
        return (1);
    }
    else
    {
        ft_printf ("label not fond [%s]\n", tmp);
        return (0);
    }
    return (0);
}

             