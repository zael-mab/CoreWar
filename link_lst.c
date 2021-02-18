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
    if (new_node->position + 1 == head->l_size)
        return (new_node);
    return (NULL);
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

void    display_nodes(t_head *head)
{
    t_node *p;

    p = NULL;
    p = head->first;
    while (p != NULL)
    {
        ft_printf ("[%d]_%s\n", p->position, p->data);
        p = p->next;
    }
}


t_node    *save_labels(t_head *labels, char *line, int pos)
{
    int j;
    int i;
    char *tmp;
    t_node *p;

    j = -1;
    while (line[++j])
        if (line[j] == LABEL_CHAR)
            break ;
    if (ft_strlen(line) > j)
    {
        tmp = ft_strncpy(ft_strnew(j), line, j);
        i = -1;
        while (++i <= j)
        {
            // ft_printf ("'%c'", tmp[i]);
            if (ft_isdigit(tmp[i]) ||  tmp[i] == 95 || (tmp[i] >= 97 && tmp[i] <= 122));
            else
                break ;
        }
        if (j == i)
        {
            if (ft_strlen(line) > j + 1){
                p = insert_node(labels, tmp, pos);
                ft_printf ("%s ---->%d\n", p->data, p->operation_num + 1);
                }
            else{
                p = insert_node(labels, tmp, pos + 1);
                ft_printf ("%s ====>%d\n", p->data, p->operation_num);
            }
            free (tmp);
            return (p);
        }
        free (tmp);
    }
    return (NULL);
}