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


void    operations(char **operat, int i)
{
    *operat = (i == 1 ? ft_strdup("live") : *operat);
    *operat = (i == 2 ? ft_strdup("ld") : *operat);
    *operat = i == 3 ? ft_strdup("st") : *operat;
    *operat = (i == 4 ? ft_strdup("add") : *operat);
    *operat = (i == 5 ? ft_strdup("sub") : *operat);
    *operat = (i == 6 ? ft_strdup("and") : *operat);
    *operat = (i == 7 ? ft_strdup("or") : *operat);
    *operat = (i == 8 ? ft_strdup("xor") : *operat);
    *operat = (i == 9 ? ft_strdup("zjmp") : *operat);
    *operat = (i == 10 ? ft_strdup("ldi") : *operat);
    *operat = (i == 11 ? ft_strdup("sti") : *operat);
    *operat = (i == 12 ? ft_strdup("fork") : *operat);
    *operat = (i == 13 ? ft_strdup("lld") : *operat);
    *operat = (i == 14 ? ft_strdup("lldi") : *operat);
    *operat = (i == 15 ? ft_strdup("lfork") : *operat);
    *operat = (i == 16 ? ft_strdup("aff") : *operat);
}

int     set_args_num(int i)
{
    if (i == 1 || i == 9 || i == 12 || i == 15 || i == 16)
        return (1);
    else if (i == 2 || i == 3 || i == 13)
        return (2);
    else
        return (3);
}

int     set_arg1(int i)
{
    if (i == 3 || i == 4 || i == 5 || i == 11 || i == 16)
        return (1);
    else if (i == 1 || i == 9 || i == 12 || i == 15)
        return (2);
    else if (i == 2 || i == 13)
        return (6);
    else
        return (7);
}


int     set_arg2(int i)
{
    if (i == 2 || i == 4 || i == 5 || i == 13)
        return (1);
    else if (i == 6 || i == 7 || i == 8 || i == 11)
        return (7);
    else if (i == 14 || i == 10)
        return (3);
    else if (i == 3)
        return (5);
    else
        return (0);
}


int     set_arg3(int i)
{
    if (i == 11)
        return (3);
    else if ((i >=4 && i <= 8) || i == 10 || i == 14)
        return (1);
    else
        return (0);
}
