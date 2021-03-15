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

void    *list_get(t_head *head)
{
    t_node  *l;
    char    *data;
    int     i;

    if (head->first == NULL)
        return (NULL);
    l = head->first;
    data = l->data;
    head->first = head->first->next;
    head->l_size--;
    i = -1;
    if (l->arg_tab)
    {
        while (l->arg_tab[++i])
            free(l->arg_tab[i]);
        free(l->arg_tab);
    }
    free(l->data);
    free(l);
    return (data);
}

void    list_del_all (t_head *head)
{
    while (head->first != NULL)
        list_get(head);
}

///////////////////////////////////
void    *list_get_lb(t_head_lb *head)
{
    t_label  *l;
    char    *data;
    if (head->first == NULL)
        return (NULL);
    l = head->first;
    data = l->data;
    head->first = head->first->next;
    head->l_size--;
    free (l->data);
    free(l);
    return (data);
}

void    list_del_all_lb (t_head_lb *head)
{
    while (head->first != NULL)
        list_get_lb(head);
}
///////////////////////////////////


t_node     *insert_node(t_head *head, void    *data)
{
    t_node  *new_node;
    t_node  *p;

    new_node = ft_memalloc (sizeof (t_node));
    new_node->data = (data);
    new_node->next = NULL;
    new_node->position = head->l_size++;
    if (head->first == NULL)
        head->first = new_node;
    else
    {
        p = head->first;
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
    }
    return (new_node->position + 1 == head->l_size ? new_node : NULL);
}

//////////////////////////////////////////
t_label     *insert_label(t_head_lb *head, void    *data, int pos)
{
    t_label  *new_node;
    t_label  *p;

    new_node = ft_memalloc (sizeof (t_label));
    new_node->data = ft_strdup(data);
    new_node->size_ind = -1;
    new_node->operation_num = pos > -1 ? pos : -1;
    new_node->next = NULL;
    new_node->position = head->l_size++;
    if (head->first == NULL)
        head->first = new_node;
    else
    {
        p = head->first;
        while (p->next != NULL)
            p = p->next;
        p->next = new_node;
    }
    return (new_node->position + 1 == head->l_size ? new_node : NULL);
}

///////////////////////////
t_label  *search_by_name(t_label *l, char* x)
{
    if (l == NULL)
        return NULL;
    if (!ft_strcmp(l->data, x))
        return (l);
    else
        return (search_by_name(l->next, x));

}

/////////////////////////////

t_label  *search_by_pos(t_label *l, size_t x)
{
    if (l == NULL)
        return NULL;
    if (l->operation_num == x)
        return (l);
    else
        return (search_by_pos(l->next, x));

}
///////////////////////

//norme


//////////////////////////////////
int     check_isdigit(char *tmp,  int j)
{
    int i;
    
    i = -1;
    while (++i <= j)
        if (ft_isdigit(tmp[i]) ||  tmp[i] == 95 || (tmp[i] >= 97 && tmp[i] <= 122));
        else
            break ;
    return (i);
}



////////////////////////////********//////////////////
// void        display_nodes(t_head *head)
// {
//     t_node *l;

//     int i;
//     l = head->first;
//     while (l)
//     {
//         head->code_size += l->command_size;
//         ft_printf("_|%.2d|\t[%s]\t",  l->position, l->data);
//         // if (l->operation_num > -1)
//             // ft_printf ("-%d-", l->size_ind);
//         if (l->code > 0)
//         {
//             ft_printf("******");
//             i = -1;
//             while (++i < 3)
//             {
//                 if (l->w_args[i] & T_DIR)
//                     ft_printf ("arg%d = DIR\n", i);
//                 if (l->w_args[i] & T_REG)
//                     ft_printf ("arg%d = REG\n", i);
//                 if (l->w_args[i] & T_IND)
//                     ft_printf ("arg%d = IND\n", i);
//                 if (l->w_args[i] & T_LAB)
//                     ft_printf ("arg%d = LIB\n", i );
//                 ft_printf ("command size = %d | command num = %d\n", l->command_size, l->op_code);
//             }
//         }
        
//         ft_putchar ('\n');
//         l = l->next;
//     }
//     ft_printf ("command size = %d\n", head->code_size);
// }
////////////////////////////********//