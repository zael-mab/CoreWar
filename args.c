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



// NORME
int         pars_args(t_node *instruction, t_asmdata *sdata, int y, t_head labels)
{
    int j;
    int x;
    int w;

    j = -1;
    w = y;
    x = 0;
    instruction->arg_tab = ft_strsplit(sdata->x + instruction->data, SEPARATOR_CHAR);   // CHANGE THAT SHIT 2 TABLES ARE YOU FUCKING ****
    sdata->op_args = ft_strsplit(sdata->x + instruction->data, SEPARATOR_CHAR);
    // sdata->p_ex_code +=1;       //

    while (sdata->op_args[++j])
    {
        sdata->y = j;
        sdata->op_args[j] = ft_strtrim(sdata->op_args[j]);        // FREE !!!
        if (ft_strlen(sdata->op_args[j]) == 0)
        {
            sdata->error += 2;
            ft_memdel((void**)sdata->op_args);
            return (0);
        }
/////////////////////////////

        x = -1;
        while (sdata->op_args[j][++x])
        {

            if (sdata->op_args[j][x] == 'r' && ft_isdigit(sdata->op_args[j][x + 1]))
            {
                if (reg_lexical_analysis (sdata, instruction, y))
                    break ;
                return (0);     // sdata->error
            }
            if (sdata->op_args[j][x] == 'r' && !ft_isdigit(sdata->op_args[j][x + 1]))
                return (0);
            else if (sdata->op_args[j][x] == '%' && sdata->op_args[j][x + 1] == ':')
            {
                if (dirl_lexical_analysis(sdata, instruction, labels, y, x))
                    break;
                return (0);
            }
            else if (sdata->op_args[j][x] == '%')                          //DIRECT_CHAR (%) and a number or label (LABEL_CHAR (:) in front of it)
            {
                if (dir_lexical_analysis(sdata, instruction, y, x))
                    break;
                return (0);
            }
            else if (sdata->op_args[j][x] == '-' || sdata->op_args[j][x] == '+' || ft_isdigit(sdata->op_args[j][x]) || sdata->op_args[j][x] == ':')
            {
                if (ind_lexical_analysis (sdata, instruction, labels, y, x))
                    break ;
                return (0);
            }
            else 
            {
                sdata->error += 2;
                return (0);
            }
        }
    }    
    if (j != g_op_tab[y].args_numb)
    {
        sdata->error = 8;
        return (0);
    }
    instruction->command_size += g_op_tab[y].encoding_code;
    ft_memdel((void**) sdata->op_args);
    return (1);
}





//////////////////////////////////////////////////
int     reg_lexical_analysis (t_asmdata *data, t_node *instruction, int y)
{
    if (!check_reg(data->op_args[data->y], g_op_tab[y].args[data->y], instruction,  *data))
        return (0);
    instruction->command_size += 1;
    instruction->w_args[data->y] = T_REG;
    instruction->w_args[data->y + 6] = 1;
    instruction->w_args[data->y + 3] = REG_CODE;
    return (1);
}


////////////////////////////////////////////
int     dirl_lexical_analysis (t_asmdata *data, t_node *instruction,t_head labels, int y, int x)
{
    if (labels.first == NULL)
        return (0);
    if (!check_dir_lebel(x + 2 + data->op_args[data->y], g_op_tab[y].args[data->y], labels))
        return (0);
    instruction->command_size += (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
    instruction->w_args[data->y + 6] = (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
    instruction->w_args[data->y] = T_LAB + T_DIR;
    instruction->w_args[data->y + 3] = DIR_CODE;
    instruction->lb += (data->y == 2 ? 4 : data->y + 1);
    return (1);
}


/////////////////////////////////////////
int     dir_lexical_analysis (t_asmdata *data, t_node *instruction, int y, int x)
{
    if (!check_dir(x + 1 + data->op_args[data->y], g_op_tab[y].args[data->y], instruction, *data))
        return (0);
    instruction->command_size += (g_op_tab[y].dir_size == 0 ? 4 : 2);
    instruction->w_args[data->y + 6] = (g_op_tab[y].dir_size == 0 ? 4 : 2);
    instruction->w_args[data->y] = T_DIR;
    instruction->w_args[data->y + 3] = DIR_CODE;
    return (1);
}

///////////////////////////////////////
int     ind_lexical_analysis (t_asmdata *data, t_node *instruction,t_head labels, int y, int x)
{
    if (data->op_args[data->y][x] == '+' || !(T_IND & g_op_tab[y].args[data->y]))
        return (0);
    if (!(ft_isalpha(data->op_args[data->y][x + 1]))) // !!!
    {
        instruction->arg[data->y] = ft_atoi(data->op_args[data->y]);
        instruction->w_args[data->y + 6] = 2;
        instruction->command_size += IND_SIZE;
        instruction->w_args[data->y] = T_IND;
        instruction->w_args[data->y + 3] = IND_CODE;
        return (1);
    }
    if (data->op_args[data->y][x] == ':')
        if (!check_ind(x + 1 + data->op_args[data->y], g_op_tab[y].args[data->y], labels))
            return (0);
    if (data->op_args[data->y][x] != ':' && !check_digit(data->op_args[data->y]))
        return (0);
    instruction->command_size += IND_SIZE;
    instruction->w_args[data->y + 6] = 2;
    instruction->w_args[data->y] = T_IND + T_LAB;
    instruction->w_args[data->y + 3] = IND_CODE;
    instruction->lb += (data->y == 2 ? 4 : data->y + 1);
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
        if (tmp[i] == 'r' && instru->arg[data.y] > 0 && instru->arg[data.y] <= REG_NUMBER && (arg & T_REG))
        {
            free(tmp);
            return(1);
        }    
    }
    ft_printf ("~6~~~~~~~~~~Error [%s]~~~~~~~~\n", tmp);
    free(tmp);
    return (0);
}


///////////////////////////////////////
int         check_dir_lebel(char *line, int arg, t_head labels)        // int !!!
{
    char    *tmp = ft_strtrim (line);
    t_node  *l;

    l  = search_by_name(labels.first, tmp);
    if ((arg & T_DIR) && l)
        return (1);
    ft_printf ("!!!Error at arg num[%s]\n", line);
    return (0);
}
