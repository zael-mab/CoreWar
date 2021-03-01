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


int         pars_args(t_node *instruction, t_asmdata *sdata, int y, t_head labels)
{
    int j;
    int x;
    int w;

    j = -1;
    w = y;
    x = 0;
    char **tab = ft_strsplit(sdata->x + instruction->data, ',');
    sdata->p_ex_code +=1;       //
    // ft_printf ("-_-_-_-_-_-_-_-_-_-%s-_-_-_-_-_-_-_-_-./_-%d\n", instruction->data, sdata->error);    /////
    while (tab[++j])
    {
        if (ft_strlen(ft_strtrim(tab[j])) == 0)
        {
            ft_printf ("~7~~~~~Error~~~~~~~~arg num %d is empty at line[%s]\n", j, instruction->data);
            return (0);
        }
/////////////////////////////

        x = -1;
        while (tab[j][++x])
        {
            
            if (tab[j][x] == 'r' && ft_isdigit(tab[j][x + 1]))
            {
                if (ft_atoi(x + 1 + tab[j]) < 1 || ft_atoi(x + 1 + tab[j]) > REG_NUMBER)
                {
                    ft_printf ("~~3~~~~~Error!~~~~~~~~~~%d \n", ft_atoi(x + 1 + tab[j]));   /////
                    return (0);
                }
                ft_putstr ("R= ");   //////
                if (!check_reg(tab[j], g_op_tab[y].args[j]))
                    return (0);
                instruction->command_size += 1;
                instruction->w_args[j] = T_REG;
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
                ft_printf ("D_Lebel= ");
                if (!check_dir_lebel(x + 2 + tab[j], g_op_tab[y].args[j], labels))
                    return (0);
                instruction->command_size += (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
                instruction->w_args[j] = T_LAB + T_DIR;
                break;
            }
// ////////////////////

            else if (tab[j][x] == '%')                          //DIRECT_CHAR (%) and a number or label (LABEL_CHAR (:) in front of it)
            {
                ft_putstr ("D= ");
                if (!check_dir(x + 1 + tab[j], g_op_tab[y].args[j]))
                    return (0);
                instruction->command_size += (g_op_tab[y].dir_size == 0 ? 4 : 2);
                instruction->w_args[j] = T_DIR;
                break ;
            }
            else if (ft_isdigit(tab[j][x]) || tab[j][x] == ':')
            {
                ft_putchar ('I');
                if (ft_atoi(x + tab[j]) < -1)
                    ft_printf ("= %d\n", ft_atoi(x + tab[j]));
                if (tab[j][x] == ':')
                    if (!check_ind(x + 1 + tab[j], g_op_tab[y].args[j], labels))
                        return (0);
                instruction->command_size += IND_SIZE;
                instruction->w_args[j] = T_IND;
                break ;
            }
        }
        ft_printf("-%s-\n", tab[j]);
    }    
    if (j != g_op_tab[y].args_numb)
    {
        ft_printf ("~5~~~~~Error at the number of arguments~~~~~~~~~~\n");  ///////
        return (0);
    }
    instruction->command_size += g_op_tab[y].encoding_code;
    return (1);
}


/////////////////////////////////////////
int         check_reg(char *line, int arg)
{
    char *tmp = ft_strtrim(line);
    int i;

    i = -1;
    while (tmp[++i])
    {
        int x = ft_atoi (1 + tmp);
        if (tmp[i] == 'r' && x > 0)
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

///////////////////////////////////////
int                check_dir_lebel(char *line, int arg, t_head labels)
{
    char *tmp = ft_strtrim (line);
    t_node *l;

    ft_printf("%s\n", line);
    l  = search(labels.first, tmp);

    if (!(arg & T_DIR))
    {
        ft_printf ("!!!Error at arg num[%s]\n", line);
        return (0);
    }
    if (l)
    {
        // ft_printf ("\t \tlable === %s\n", l->data);
        return (1);
    }
    return (0);
}
