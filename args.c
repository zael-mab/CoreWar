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


int         check_reg(char *line, int arg);


int         pars_args(char  *instruction, t_asmdata *sdata, int y, t_head labels)
{
    int j;
    int x;
    int w;

    j = -1;
    w = y;
    x = 0;
    char **tab = ft_strsplit(instruction, ',');

    ft_printf ("-_-_-_-_-_-_-_-_-_-%s-_-_-_-_-_-_-_-_-./_-%d\n", instruction, sdata->error);    /////

    while (tab[++j])
    {
        if (ft_strlen(ft_strtrim(tab[j])) == 0)
        {
            ft_printf ("~7~~~~~Error~~~~~~~~arg num %d is empty at line[%s]\n", j, instruction);
            return (0);
        }
/////////////////////////////

        x = -1;
        while (tab[j][++x])
        {
            
            if (tab[j][x] == 'r' && ft_isdigit(tab[j][x + 1]))
            {
                if (ft_atoi(x + 1 + tab[j]) < 1 || ft_atoi(x + 1 + tab[j]) > 16)
                {
                    ft_printf ("~~3~~~~~Error!~~~~~~~~~~%d \n", ft_atoi(x + 1 + tab[j]));   /////
                    return (0);
                }
                ft_putchar ('R');   //////
                check_reg(tab[j], op_tab[y].args[j]);
                break ;
            }
// //////////////////////

            if (tab[j][x] == 'r' && !ft_isdigit(tab[j][x + 1]))
            {
                ft_printf("~~4~~~~~~~~Error~~~~~~~~~\n");   ///////
                return (0);
            }
            else if (tab[j][x] == '%' && tab[j][x + 1] == ':')
            {
                if (labels.first == NULL)
                    return (0);
                check_dir_lebel(3 + tab[j], op_tab[y].args[j], labels);
                ft_printf ("D_Lebel");
                break;
            }
// ////////////////////

            else if (tab[j][x] == '%')                          //DIRECT_CHAR (%) and a number or label (LABEL_CHAR (:) in front of it)
            {
                // check_dir();
                ft_putchar ('D');
                break ;
            }
            else if (ft_isdigit(tab[j][x]))
            {
                ft_putchar ('I');
                // check_ind();
                break ;
            }
        }
        ft_printf("-%s-\n", tab[j]);
    }    
    if (j != op_tab[y].args_numb)
    {
        ft_printf ("~5~~~~~Error at the number of arguments~~~~~~~~~~\n");  ///////
        return (0);
    }
    return (1);
}


int         check_reg(char *line, int arg)
{
    char *tmp = ft_strtrim(line);
    int i;

    i = -1;
    while (tmp[++i])
    {
        if (tmp[i] == 'r' && ft_atoi(1 + tmp) > 0)
        {
            if (!(arg & T_REG))
            {
                ft_printf ("Error at arg num[%s]\n", tmp);
                break ;
            }
            else
                break;
        }
        else
        {
            ft_printf ("~6~~~~~~~~~~Error [%s]~~~~~~~~\n", tmp);
            break ;
        }
    }

    free(tmp);
    return (1);
}


int                check_dir_lebel(char *line, int arg, t_head labels)
{
    char *tmp = ft_strtrim (line);
    t_node *l;

    ft_printf("%s\n", line);
    l  = search(labels.first, tmp);
    // ft_memdel ((void *)tmp);

    if (!(arg & T_DIR))
    {
        ft_printf ("!!!Error at arg num[%s]\n", line);
        ft_memdel((void *) l);
        // ft_memdel ((void *)tmp);
        return (0);
    }
    if (l)
    {
        ft_printf ("\t \tlable === %s\n", l->data);
        ft_memdel((void *) l);
        // list_get(l);
        return (1);
    }
    return (0);
}
