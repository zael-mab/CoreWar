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
    if (head->first == NULL)
        return (NULL);
    l = head->first;
    data = l->data;
    head->first = head->first->next;
    head->l_size--;
    free (l);
    return (data);
}

void    list_del_all (t_head *head)
{
    while (head->first != NULL)
        list_get(head);
}
///////////////////////////////////


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

///////////////////////////
t_node  *search_by_name(t_node *l, char* x)
{
    if (l == NULL)
        return NULL;
    if (!ft_strcmp(l->data, x))
        return (l);
    else
        return (search_by_name(l->next, x));

}

/////////////////////////////

t_node  *search_by_pos(t_node *l, int x)
{
    if (l == NULL)
        return NULL;
    if (l->operation_num == x)
        return (l);
    else
        return (search_by_pos(l->next, x));

}
///////////////////////


void        display_nodes(t_head *head)
{
    t_node *l;

    int i;
    l = head->first;
    while (l)
    {
        head->code_size += l->command_size;
        ft_printf("_|%.2d|\t[%s]\t",  l->position, l->data);
        if (l->operation_num > -1)
            ft_printf ("-%d-", l->size_ind);
        if (l->code > 0)
        {
            ft_printf("******");
            i = -1;
            while (++i < 3)
            {
                if (l->w_args[i] & T_DIR)
                    ft_printf ("arg%d = DIR\n", i);
                if (l->w_args[i] & T_REG)
                    ft_printf ("arg%d = REG\n", i);
                if (l->w_args[i] & T_IND)
                    ft_printf ("arg%d = IND\n", i);
                if (l->w_args[i] & T_LAB)
                    ft_printf ("arg%d = LIB\n", i );
                ft_printf ("command size = %d | command num = %d\n", l->command_size, l->op_code);
            }
        }
        
        ft_putchar ('\n');
        l = l->next;
    }
    ft_printf ("command size = %d\n", head->code_size);

}


//norme
t_node      *save_labels(t_head *labels, char *line, t_head *head)
{
    int     j;
    char    *tmp;
    static  int tmp_post;
    t_node  p;                       //[  marker: 

    j = -1;
    ft_bzero(&p, sizeof (t_node));
    while (line[++j] && line[j] != LABEL_CHAR);
    if (ft_strlen(line) > j)
    {
        tmp = ft_strncpy(ft_strnew(j), line, j);
        if (j == check_isdigit(tmp, j))
        {
            if (ft_strlen(line) > j + 1)
            {
                p = *insert_node (head, ft_strtrim (j + 1 +line), -1);					//	insert eash line 
                insert_node(labels, tmp, p.position);
            }
            else
                insert_node(labels, tmp, tmp_post);
            return (NULL);
        }
        free (tmp);
    }
    p = *insert_node (head, line, -1); 
    tmp_post = p.position + 1;	 
    return (NULL);
}

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