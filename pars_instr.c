
#include "asm.h"

void    add_encodin_code(t_asmdata *sdata, t_node *instruct)
{
    sdata->x = 2;
    while (++sdata->x < 6)
    {
        if (sdata->x == 3)
            init_encodin_byte(instruct, sdata->x, 2 * sdata->x);
        if (sdata->x == 5)
            init_encodin_byte(instruct, sdata->x, sdata->x - 3);
        if (sdata->x == 4)
            init_encodin_byte(instruct, sdata->x, sdata->x);
    }
}

/////////////////////////////////////////////////
void        init_encodin_byte(t_node *instr, int p, int shift)
{
    if (instr->w_args[p] == REG_CODE)
        instr->encodin += REG_CODE << shift;
    if (instr->w_args[p] == DIR_CODE)
        instr->encodin += DIR_CODE << shift;
    if (instr->w_args[p] == IND_CODE)
        instr->encodin += IND_CODE << shift;
}


int             check_oper(t_node *instruct, t_head_lb labels, t_head *head, t_asmdata *data)
{
    int         x;
    char        *tmp;
    t_label      *l;

    tmp = ft_strncpy(ft_strnew(5), instruct->data, data->x);       //CHANGE that just point to it, no need to allocate I think !.
    x = -1;
    while (++x < 17)
    {
        if (!ft_strcmp(tmp, g_op_tab[x].name))
        {
            if ((l = search_by_pos(labels.first, instruct->position)))
                l->size_ind = instruct->command_size + head->code_size;
            if (!pars_args(instruct, data, x, labels))
            {
                // data->error += 4;
                // if (data->error & 8)
                //     ft_printf ("Error: number of arguments ,line '%10s'\n", instruct->data);
                // if (data->error & 2)
                //     ft_printf ("Error: argument [%d] is empty  ,line '%10s'\n", data->y + 1, instruct->data);
                // if (data->error & 4)
                //     ft_printf ("Error at line '%10s'\n", instruct->data);
                ft_memdel((void**) data->op_args);
                free (tmp);
                return (-1);
            }
            instruct->command_size += 1;
            instruct->code = (x == 17 ? -1 : g_op_tab[x].op_code);
            instruct->arg_num = g_op_tab[x].args_numb;
            instruct->encodin_code = g_op_tab[x].encoding_code;
            if (instruct->encodin_code > 0)
                add_encodin_code(data, instruct);
            break ;
        }
    }
    free (tmp);
    return(x);
}

///////////////////////////////////////////////
int         pars_instructions(t_head *head, t_head_lb labels, t_asmdata *sdata)       //REG_NUMBER
{
    t_node  *instruct;
    int     x;

    instruct = NULL;
    instruct = head->first;
    sdata->error = -1;
    while (instruct != NULL)
    {
        sdata->x = -1;
        while (instruct->data[++sdata->x])
            if (instruct->data[sdata->x] < 'a' || instruct->data[sdata->x] > 'z')
                break;
        if (sdata->x == 0 && ft_strlen (instruct->data) > 0)
        {
            ft_printf("wrang command line [%s]\n", instruct->data);
            sdata->error = 1;
            return (0);
        }
        if (sdata->x > 0)
        {
            x = check_oper(instruct, labels, head, sdata);
            if (x == 17 || x == -1)
            {
                sdata->error = 1;
                return (0);
            }
            head->code_size += instruct->command_size;
        }
        instruct = instruct->next;
    }
    return (1);
}