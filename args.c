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
 

int         pars_args(t_node *instruction, t_asmdata *sdata, int y, t_head_lb labels)
{
    int j;
    int c;

    c = 0;
    j = sdata->x;
    instruction->arg_tab = ft_strsplit(sdata->x + instruction->data, SEPARATOR_CHAR);   // CHANGE THAT SHIT 2 TABLES ARE YOU FUCKING ****
    sdata->op_args = ft_strsplit(sdata->x + instruction->data, SEPARATOR_CHAR);
    while (instruction->data[++j])
        if (instruction->data[j] == ',')
            c++;
    j = -1;
    while (sdata->op_args[++j])
    {
        sdata->y = j;
        sdata->op_args[j] = ft_strtrim(sdata->op_args[j]);        // FREE !!!
        if (!trt_arg(sdata, instruction, labels, j, y))
            return (0);
    }
    if (j != g_op_tab[y].args_numb || c + 1 != g_op_tab[y].args_numb)
    {
        sdata->error = 8;
        return (0);
    }
    instruction->command_size += g_op_tab[y].encoding_code;
    return (1);
}


int         trt_arg(t_asmdata *data, t_node *instruction, t_head_lb labels, int j, int y)
{
    int     x;

    x = -1;
    if (ft_strlen(data->op_args[j]) == 0)
    {
        // data->error += 2;        // fucking fix it!
        ft_memdel((void**)data->op_args);
        return (0);
    }
    while (data->op_args[j][++x])
    {
        if (data->op_args[j][x] == 'r' && ft_isdigit(data->op_args[j][x + 1]))
            return (reg_lexical_analysis (data, instruction, y));     // data->error
        if (data->op_args[j][x] == 'r' && !ft_isdigit(data->op_args[j][x + 1]))
            return (0);
        else if (data->op_args[j][x] == '%' && data->op_args[j][x + 1] == ':')
            return (dirl_lexical_analysis(data, instruction, labels, y, x));
        else if (data->op_args[j][x] == '%')                          //DIRECT_CHAR (%) and a number or label (LABEL_CHAR (:) in front of it)
            return (dir_lexical_analysis(data, instruction, y, x));
        else if (data->op_args[j][x] == '-' || data->op_args[j][x] == '+' || ft_isdigit(data->op_args[j][x]) || data->op_args[j][x] == ':')
            return (ind_lexical_analysis (data, instruction, labels, y, x));
        else 
        {
            data->error += 2;
            return (0);
        }
    }
    return (1);
}


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


int     dirl_lexical_analysis (t_asmdata *data, t_node *instruction,t_head_lb labels, int y, int x)
{
    if (labels.first == NULL)
        return (0);
    if (!check_dir_lebel(x + 2 + data->op_args[data->y], g_op_tab[y].args[data->y], labels))
        return (0);
    instruction->w_args[data->y + 6] = (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
    instruction->w_args[data->y] = T_LAB + T_DIR;
    instruction->w_args[data->y + 3] = DIR_CODE;
    instruction->command_size += (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
    instruction->lb += (data->y == 2 ? 4 : data->y + 1);
    return (1);
}

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

int     ind_lexical_analysis (t_asmdata *data, t_node *instruction,t_head_lb labels, int y, int x)
{
    if (data->op_args[data->y][x] == '+' || !(T_IND & g_op_tab[y].args[data->y]))
        return (0);
    if (check_digit(data->op_args[data->y]) && !(ft_isalpha(data->op_args[data->y][x + 1]))) // !!!
    {
        instruction->arg[data->y] = ft_atoi(data->op_args[data->y]);
        instruction->w_args[data->y + 6] = 2;
        instruction->w_args[data->y] = T_IND;
        instruction->w_args[data->y + 3] = IND_CODE;
        instruction->command_size += IND_SIZE;
        return (1);
    }
    if (data->op_args[data->y][x] == ':')
    {
        if (!check_ind(x + 1 + data->op_args[data->y], g_op_tab[y].args[data->y], labels))
            return (0);
        instruction->w_args[data->y + 6] = 2;
        instruction->w_args[data->y] = T_IND + T_LAB;
        instruction->w_args[data->y + 3] = IND_CODE;
        instruction->lb += (data->y == 2 ? 4 : data->y + 1);
        instruction->command_size += IND_SIZE;
    }
    return (1);
}
