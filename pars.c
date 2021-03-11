/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:48:24 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/03 14:22:42 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

// name;
// Comment;
// Executable code;
//

//              FOR PARS:
// in one line - one instruction. "sequence of instructions"
//      Empty lines, comments, as well as extra tabs or spaces are ignored.

// verything between the character '#' and the end of the line is considered a comment. 

// An empty string is a valid champion name : [ .name "" ]
//      but But lack of the string is an error: [ .name  ] (same case for the comment)

// Also, in the file .s must be present champion's comment.

// the command  " .extend " -and all other commands excepting '.name' and '.comment'- detected as an error


//                  FOR EXUECUTABLE CODE:
//  Assembly language has a rule one instruction per line. The new line character \n means both end
//       of line and end of instruction. So instead of ; as for C language, we will use \n.

//      Each redcode instruction contains 3 parts : Opcode itself, the source address A-field 
//          and the destination address B-field.

int         search_for_exention(char *line, t_asmdata *data)
{
    int j;

    j = -1;
    while (line[++j])
        if (line[j] == '.' && ((ft_strscmp(NAME_CMD_STRING, j + line, 0, 5) == 0)
        || ft_strscmp(COMMENT_CMD_STRING, j + line, 0, 5) == 0))
        {
            data->e = 0;
            data->s = 0;
            data->error = -1;
            return (j);
        }
    return (-1);
}



//////////////////////////////////////
int         check_champion (char *line, t_asmdata *sdata)
{
    int     j = 0;

    j = search_for_exention(line, sdata);
    sdata->n = (ft_strscmp(NAME_CMD_STRING,j + line, 0, 5) == 0) ? 1 : sdata->n;
    sdata->c = (ft_strscmp(COMMENT_CMD_STRING,j + line, 0, 8) == 0) ? 1 : sdata->c;
    j = -1;
    while (line[++j])
    {
        if (line[j] == '"' && sdata->s && !sdata->e)
            sdata->e = j + 1;
        if (line[j] == '"' && !sdata->s)
            sdata->s = j + 1;
    }
    // if (sdata->n && sdata->e && sdata->s && (sdata->e - sdata->s) > PROG_NAME_LENGTH)
    //     return(0);
    // if (sdata->c && sdata->e && sdata->s && (sdata->e - sdata->s) > COMMENT_CHAR)
    //     return(0);
    if (!(pars_chmp_nm_cm(sdata, line)))
        return (0);
    return (1);
}

//////////////////////////////////////
int         pars_chmp_nm_cm(t_asmdata *sdata, char *line)
{
    if (sdata->e > 0 && (sdata->n == 1 || sdata->c == 1) && ft_strlen(ft_strtrim(sdata->e + line)) != 0) // check the restof line "something"x
    {
        ft_printf("#Error in the line[%s] \n", line);
        return (0);
    }
    if (sdata->n == 1 && sdata->s && sdata->e && sdata->error == -1)
        if ((sdata->name = ft_strscpy(ft_strnew(PROG_NAME_LENGTH), line, sdata->s, sdata->e)))
            sdata->n = -1;
    if (sdata->c == 1 && sdata->s && sdata->e && sdata->error == -1)
        if((sdata->comment = ft_strscpy(ft_strnew(COMMENT_LENGTH), line, sdata->s, sdata->e)))
            sdata->c = -1;

    if (sdata->s && (sdata->c == 1 || sdata->n == 1))
    {
        sdata->error++;
        if (sdata->n == 1)
            join(line, sdata, &sdata->name, PROG_NAME_LENGTH);
        if (sdata->c == 1)
            join (line, sdata, &sdata->comment, COMMENT_LENGTH);
        return (1);
    }
    return(1);
}


///////////////////////////////////////
int         join (char *line, t_asmdata *sdata, char **cmd, int v)
{
    char    *tmp;

    tmp = ft_strnew(ft_strlen(line));
    if (sdata->error == 0)
    {
        *cmd = ft_strjoin (ft_strnew(v), line + sdata->s);
        *cmd = ft_strjoin (*cmd, "\n");
    }
    if (sdata->error > 0 && !sdata->e)
    {
        *cmd = ft_strjoin (*cmd, line);
        *cmd = ft_strjoin (*cmd, "\n");
    }
    if (sdata->error > 0 && sdata->e)
    {
        *cmd = ft_strjoin(*cmd, ft_strscpy(tmp, line, 0, sdata->e));
        sdata->error = -1;
        sdata->c = (sdata->c == 1 ? -1 : sdata->c);
        sdata->n = (sdata->n == 1 ? -1 : sdata->n);
    }
    free (tmp);
    return (1);
}



//////////////////////////////////////////////////
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
            ft_printf("wrang command [%s]\n", instruct->data);
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
                data->error += 4;
                if (data->error & 8)
                    ft_printf ("Error: number of arguments ,line '%10s'\n", instruct->data);
                if (data->error & 2)
                    ft_printf ("Error: argument [%d] is empty  ,line '%10s'\n", data->y + 1, instruct->data);
                if (data->error & 4)
                    ft_printf ("Error at line '%10s'\n", instruct->data);
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
