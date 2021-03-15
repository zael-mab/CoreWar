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


///////////////////////////////////////
int                check_ind(char *line, int arg, t_head_lb labels)
{
    char *tmp;
    t_label *l;

    tmp = ft_strtrim (line);
    l  = search_by_name(labels.first, tmp);
    free (tmp);
    if ((arg & T_IND) && l)
        return (1);
    ft_printf ("Error at arg num[%s]\n", line);
    return (0);
}


/////////////////////////////////////////////////////
int         check_reg(char *line, int arg, t_node *instru, t_asmdata data)
{
    char *tmp = ft_strtrim(line);
    int i;

    i = -1;
    while (tmp[++i])
    {
        instru->arg[data.y] = ft_atoi (1 + tmp);
        if (tmp[i] == 'r' && instru->arg[data.y] > 0 && instru->arg[data.y] <= REG_NUMBER && (arg & T_REG))
        {
            free(tmp);
            return(1);
        }    
    }
    free(tmp);
    return (0);
}


///////////////////////////////////////
int         check_dir_lebel(char *line, int arg, t_head_lb labels)        // int !!!
{
    char    *tmp = ft_strtrim (line);
    t_label  *l;

    l  = search_by_name(labels.first, tmp);
    free (tmp);
    if ((arg & T_DIR) && l)
        return (1);
    return (0);
}

int     check_digit(char *line)
{
    int x;

    x = -1;
    while (line[++x])
    {
        if (x == 0 && line[x] == '-')
            x++;
        if (!ft_isdigit(line[x]))
            return (0);
    }
    return (1);
}