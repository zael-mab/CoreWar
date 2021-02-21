/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 17:44:27 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/21 17:44:35 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


int         pars_args(char  *instruction, t_op *op)
{
    int j;
    int x = 0;

    j = -1;
    char **tab = ft_strsplit(instruction, ',');
    ft_printf ("-_-_-_-_-_-_-_-_-_-%s-_-_-_-_-_-\n", op->name);
    while (tab[++j])
    {
        x = -1;
        while (tab[j][++x])
        {
            if (tab[j][x] == 'r' && ft_isdigit(tab[j][x + 1]))
            {
                ft_putchar ('R');
                break ;
            }
            if (tab[j][x] == '%')
            {
                ft_putchar ('D');
                break ;
            }
            if (ft_isdigit(tab[j][x]))
            {
                ft_putchar ('I');
                break ;
            }
        }
        ft_printf("[%s]\n", tab[j]);

    }
    return (1);
}
