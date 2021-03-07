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




int         pars_args(t_node *instruction, t_asmdata *sdata, int y, t_head labels)
{
    int j;
    int x;
    int w;

    j = -1;
    w = y;
    x = 0;
    sdata->op_args = ft_strsplit(sdata->x + instruction->data, SEPARATOR_CHAR);
    instruction->arg_tab = ft_strsplit(sdata->x + instruction->data, SEPARATOR_CHAR);   // CHANGE THAT SHIT 2 TABLES ARE YOU FUCKING ****
    sdata->p_ex_code +=1;       //


    while (sdata->op_args[++j])
    {
        ft_printf ("\t\t\t\t\t****[[%s==%s]]\n", instruction->data, sdata->op_args[j]);
        if (ft_strlen(ft_strtrim(sdata->op_args[j])) == 0)
        {
            ft_printf ("~7~~~~~Error~~~~~~~~arg num %d is empty at line[%s]\n", j, instruction->data);
            ft_memdel((void**)sdata->op_args);
            return (0);
        }
/////////////////////////////

        x = -1;
        while (sdata->op_args[j][++x])
        {
            
            sdata->y = j;
            if (sdata->op_args[j][x] == 'r' && ft_isdigit(sdata->op_args[j][x + 1]))
            {
                if (ft_atoi(x + 1 + sdata->op_args[j]) < 1 || ft_atoi(x + 1 + sdata->op_args[j]) > REG_NUMBER)
                {
                    ft_printf ("~~3~~~~~Error!~~~~~~~~~~%d \n", ft_atoi(x + 1 + sdata->op_args[j]));   /////
                    return (0);
                }
                // ft_putstr ("R= ");   //////
                if (!check_reg(sdata->op_args[j], g_op_tab[y].args[j], instruction,  *sdata))
                    return (0);
                instruction->command_size += 1;
                instruction->w_args[j] = T_REG;
                instruction->w_args[j + 6] = 1;
                instruction->w_args[j + 3] = REG_CODE;
                break ;
            }


// /////////////////////////////

            if (sdata->op_args[j][x] == 'r' && !ft_isdigit(sdata->op_args[j][x + 1]))
            {
                ft_printf("~~4~~~~~~~~Error~~~~~~~~~\n");   ///////
                return (0);
            }


//////////////////////////////////////////////

            else if (sdata->op_args[j][x] == '%' && sdata->op_args[j][x + 1] == ':')
            {
                if (labels.first == NULL)
                    return (0);
                // ft_printf ("D_Lebel= ");
                if (!check_dir_lebel(x + 2 + sdata->op_args[j], g_op_tab[y].args[j], labels))
                    return (0);
                instruction->command_size += (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
                instruction->w_args[j + 6] = (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
                instruction->w_args[j] = T_LAB + T_DIR;
                instruction->w_args[j + 3] = DIR_CODE;
                instruction->lb += (j == 2 ? 4 : j + 1);
                break;
            }
// ///////////////////////////////////


            else if (sdata->op_args[j][x] == '%')                          //DIRECT_CHAR (%) and a number or label (LABEL_CHAR (:) in front of it)
            {
                // ft_putstr ("D= ");
                if (!check_dir(x + 1 + sdata->op_args[j], g_op_tab[y].args[j], instruction, *sdata))
                    return (0);
                instruction->command_size += (g_op_tab[y].dir_size == 0 ? 4 : 2);
                instruction->w_args[j + 6] = (g_op_tab[y].dir_size == 0 ? 4 : 2);
                instruction->w_args[j] = T_DIR;
                instruction->w_args[j + 3] = DIR_CODE;
                break ;
            }
// ///////////////////////////////////////

            else if (ft_isdigit(sdata->op_args[j][x]) || sdata->op_args[j][x] == ':')
            {
                // ft_putchar ('I');
                if (ft_atoi(x + sdata->op_args[j]) > -1 && !(ft_isalpha(sdata->op_args[j][x + 1]))) // !!!
                {
                    instruction->arg[j] = ft_atoi(x + sdata->op_args[j]);
                    instruction->w_args[j + 6] = 2;
                    instruction->command_size += IND_SIZE;
                    instruction->w_args[j] = T_IND;
                    instruction->w_args[j + 3] = IND_CODE;
                    break ;
                }
////////////////////////////////////////
                if (sdata->op_args[j][x] == ':')
                    if (!check_ind(x + 1 + sdata->op_args[j], g_op_tab[y].args[j], labels))
                        return (0);
                ft_printf ("\t\t^^^^^^^^^^^^^^^^^^%s^^^^^^^^^^^^^^^^\n", sdata->op_args[j]);
                instruction->command_size += IND_SIZE;
                instruction->w_args[j + 6] = 2;
                instruction->w_args[j] = T_IND + T_LAB;
                instruction->w_args[j + 3] = IND_CODE;
                instruction->lb += (j == 2 ? 4 : j + 1);
                break ;
            }
        }
        ft_printf("-%s-\n", sdata->op_args[j]);
    }    
    if (j != g_op_tab[y].args_numb)
    {
        ft_printf ("~5~~~~~Error at the number of arguments~~~~~~~~~~\n");  ///////
        return (0);
    }
    instruction->command_size += g_op_tab[y].encoding_code;
    ft_memdel((void**) sdata->op_args);

    return (1);
}


/////////////////////////////////////////
int         check_reg(char *line, int arg, t_node *instru, t_asmdata data)
{
    char *tmp = ft_strtrim(line);
    int i;

    i = -1;
    while (tmp[++i])
    {
        instru->arg[data.y] = ft_atoi (1 + tmp);
        
        if (tmp[i] == 'r' && instru->arg[data.y] > 0)
        {
            if (!(arg & T_REG))
            {
                ft_printf ("Error at arg num[%s]\n", tmp);
                return(0);
            }
            else
                break;
        }
        else
        {
            ft_printf ("~6~~~~~~~~~~Error [%s]~~~~~~~~\n", tmp);
            return(0);
        }
    }
    free(tmp);
    return (1);
}

///////////////////////////////////////

int         check_dir_lebel(char *line, int arg, t_head labels)        // int !!!
{
    char    *tmp = ft_strtrim (line);
    t_node  *l;

    //ft_printf("%s\n", line);
    l  = search_by_name(labels.first, tmp);

    if (!(arg & T_DIR))
    {
        ft_printf ("!!!Error at arg num[%s]\n", line);
        return (0);
    }
    if (l)
        return (1);
    // {
        // ft_printf ("\t \tlable === %s\n", l->data);
    // }
    return (0);
}
