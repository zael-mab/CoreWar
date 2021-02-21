/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 15:32:58 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/02 18:25:05 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h"

void    init_head(t_head *head)
{
    head = ft_memalloc (sizeof (t_head));
    head->first = NULL;
    head->l_size = 0;
}
///////////////////////////////////

void        init_op(t_hop *op)
{
    op = ft_memalloc(sizeof (t_hop));
    op->pos = 1;
    op->fopr = NULL;
}


t_node     *insert_node(t_head *head, void    *data, int pos)
{
    t_node  *new_node;
    t_node  *p;

    new_node = ft_memalloc (sizeof (t_node));
    new_node->data = data;
    new_node->operation_num = pos > -1 ? pos : -1;
    new_node->next = NULL;
    if (head->first == NULL)
    {
        head->first = new_node;
        new_node->position = head->l_size++;
    }
    else
    {
        p = head->first;
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
        new_node->position = head->l_size++;
    }
    return (new_node->position + 1 == head->l_size ? new_node : NULL);
}


t_node  *search(t_node *l, void* x)
{
    if (l == NULL)
        return NULL;
    if (l->data == x)
        return (l);
    else
        return (search(l->next, x));

}


t_op  *op_search(t_op *l, void *x)
{
    if (l == NULL)
        return NULL;
    if (!ft_strcmp(l->name , x))
        return (l);
    else
        return (op_search(l->nop, x));
}

t_node    *save_labels(t_head *labels, char *line, t_head *head)
{
    int j;
    int i;
    char *tmp;
    static int tmp_post;
    t_node p;                       //[  marker: 
    t_node t;                       //  # End of file  ]   if a label didn't followed by '\n' at the end of file it's an error fix it .


    ft_bzero(&p, sizeof (t_node));
    ft_bzero(&t, sizeof (t_node));
    j = -1;
    while (line[++j])
        if (line[j] == LABEL_CHAR)
            break ;


///////////////////////
    if (ft_strlen(line) > j)
    {
        tmp = ft_strncpy(ft_strnew(j), line, j);
        i = -1;
        while (++i <= j)
            if (ft_isdigit(tmp[i]) ||  tmp[i] == 95 || (tmp[i] >= 97 && tmp[i] <= 122));
            else
                break ;

/////////////////
        if (j == i)
        {
            if (ft_strlen(line) > j + 1)
            {
                p = *insert_node (head, ft_strtrim (j + 1 +line), -1);					//	insert eash line 
                t = *insert_node(labels, tmp, p.position);
            }
            else
                t = *insert_node(labels, tmp, tmp_post);
            return (NULL);
        }
        free (tmp);
    }
    p = *insert_node (head, line, -1); 
    tmp_post = p.position + 1;	 
    return (NULL);
}




//////////////////////////////////
void        set_op_table(t_hop *op)
{
    int i;

    i = 0;
    while (++i < 17)
        creat_op_table(op, i);
}


/////////////////////////////////
void        creat_op_table(t_hop *op, int i)
{
    t_op    *n_op;
    t_op    *l;
    char    *name;

    l = NULL;
    n_op = ft_memalloc (sizeof (t_op));
    n_op->nop = NULL;
    operations(&name, i);
    n_op->name = name;
    n_op->code = i;
    n_op->args_num = set_args_num(i);
    n_op->arg1 = set_arg1(i);
    n_op->arg2 = set_arg2(i);
    n_op->arg3 = set_arg3(i);
    if (op->fopr == NULL)
        op->fopr = n_op;
    else
    {
        l = op->fopr;
        while (l->nop != NULL)
            l = l->nop;
        l->nop = n_op;
    }
}

///////////////////////////////////
void        displa_op(t_hop *op)
{
    t_op *tmp;

    tmp = op->fopr;
    while (tmp)
    {
        ft_printf ("'%s'|num =  %d \t|", tmp->name, tmp->args_num);
        if (tmp->arg1 & T_REG)
            ft_printf (" reg ");
        if (tmp->arg1 & T_DIR)
            ft_printf (" dir ");
        if (tmp->arg1 & T_IND)
            ft_printf (" ind ");
        ft_putchar (',');
        if (tmp->arg2 & T_REG)
            ft_printf (" reg ");
        if (tmp->arg2 & T_DIR)
            ft_printf (" dir ");
        if (tmp->arg2 & T_IND)
            ft_printf (" ind ");
        ft_putchar (',');
        if (tmp->arg3 & T_REG)
            ft_printf (" reg ");
        if (tmp->arg3 & T_DIR)
            ft_printf (" dir ");
        if (tmp->arg3 & T_IND)
            ft_printf (" ind ");
        ft_putchar ('\n');

        tmp = tmp->nop;
    }
}

void    display_nodes(t_head *head)
{
    t_node *p;

    p = NULL;
    p = head->first;
    while (p != NULL)
    {
        ft_printf ("[%d]_%s ", p->position, p->data);
        if (p->operation_num > -1)
            ft_printf ("goto->%d", p->operation_num);
        ft_putchar ('\n');
        p = p->next;
    }
}
/////////////////////////////////