
#include "asm.h"

int     reg_lexical_analysis(t_asmdata *data, t_node *instruction, int y)
{
    if (!check_reg(data->op_tb[data->y], g_op_tab[y].args[data->y], instruction,  *data))
        return (print_arg_error(*instruction, data, data->y, 0));
    instruction->command_size += 1;
    instruction->w_args[data->y] = T_REG;
    instruction->w_args[data->y + 6] = 1;
    instruction->w_args[data->y + 3] = REG_CODE;
    return (1);
}


int     dirl_lexical_analysis(t_asmdata *data, t_node *instruction,t_head_lb labels, int y, int x)
{
    if (!check_dir_lebel(x + 2 + data->op_tb[data->y], g_op_tab[y].args[data->y], labels))
        return (print_arg_error(*instruction, data, data->y, ((g_op_tab[y].args[data->y]) & T_DIR) > 0));
    instruction->w_args[data->y + 6] = (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
    instruction->w_args[data->y] = T_LAB + T_DIR;
    instruction->w_args[data->y + 3] = DIR_CODE;
    instruction->command_size += (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
    instruction->lb += (data->y == 2 ? 4 : data->y + 1);
    return (1);
}

int     dir_lexical_analysis (t_asmdata *data, t_node *instruction, int y, int x)
{
    if (!check_dir(x + 1 + data->op_tb[data->y], g_op_tab[y].args[data->y], instruction, *data))
        return (print_arg_error(*instruction, data, data->y, 0));
    instruction->command_size += (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
    instruction->w_args[data->y + 6] = (g_op_tab[y].dir_size == 0 ? DIR_SIZE : IND_SIZE);
    instruction->w_args[data->y] = T_DIR;
    instruction->w_args[data->y + 3] = DIR_CODE;
    return (1);
}

int     ind_lexical_analysis (t_asmdata *data, t_node *instruction,t_head_lb labels, int y, int x)
{
    if (data->op_tb[data->y][x] == '+' || !(T_IND & g_op_tab[y].args[data->y]))
        return (print_arg_error(*instruction, data, data->y, 0));
    if (check_digit(data->op_tb[data->y]) && !(ft_isalpha(data->op_tb[data->y][x + 1]))) // !!!
    {
        instruction->arg[data->y] = ft_atoi(data->op_tb[data->y]);
        instruction->w_args[data->y + 6] = 2;
        instruction->w_args[data->y] = T_IND;
        instruction->w_args[data->y + 3] = IND_CODE;
        instruction->command_size += IND_SIZE;
        return (1);
    }
    if (data->op_tb[data->y][x] == ':')
    {
        if (!check_ind(x + 1 + data->op_tb[data->y], g_op_tab[y].args[data->y], labels))
            return (print_arg_error(*instruction, data, data->y, ((g_op_tab[y].args[data->y]) & T_DIR)));
        instruction->w_args[data->y + 6] = 2;
        instruction->w_args[data->y] = T_IND + T_LAB;
        instruction->w_args[data->y + 3] = IND_CODE;
        instruction->lb += (data->y == 2 ? 4 : data->y + 1);
        instruction->command_size += IND_SIZE;
    }
    return (1);
}
