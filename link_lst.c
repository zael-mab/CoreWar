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


boolean     insert_node(t_head *head, void    *data)
{
    t_node  *new_node;
    t_node  *p;

    new_node = ft_memalloc (sizeof (t_node));
    new_node->data = ft_strdup(data);
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
        return (1);
    return (0);
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
        ft_printf ("%s\n", p->data);
        p = p->next;
    }
}