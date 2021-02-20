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
        ft_printf ("[%d]_%s ", p->position, p->data);
        if (p->operation_num > -1)
            ft_printf ("goto->%d", p->operation_num);
        ft_putchar ('\n');
        p = p->next;
    }
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


/////////////



/////////////
    if (ft_strlen(line) > j)
    {
        tmp = ft_strncpy(ft_strnew(j), line, j);
        i = -1;
        while (++i <= j)
            if (ft_isdigit(tmp[i]) ||  tmp[i] == 95 || (tmp[i] >= 97 && tmp[i] <= 122));
            else
                break ;

///////////
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

void    operations(char **operat, int i);

void        creat_op_table(t_asmdata *sdata)
{
    int i;
    char *operat;

    i = -1;
    operat =ft_strnew(5);
    sdata->op_tabe = (char **)malloc (16 * sizeof (char *));
    while (++i < 16)
    {
        operations(&operat, i);
        sdata->op_tabe[i] = (char *)malloc (ft_strlen(operat) * sizeof (char));
        ft_strcpy(sdata->op_tabe[i],operat);
        free (operat);
    }
}

void    operations(char **operat, int i)
{
    *operat = (i == 0 ? ft_strdup("live") : *operat);
    *operat = (i == 1 ? ft_strdup("ld") : *operat);
    *operat = i == 2 ? ft_strdup("st") : *operat;
    *operat = (i == 3 ? ft_strdup("add") : *operat);
    *operat = (i == 4 ? ft_strdup("sub") : *operat);
    *operat = (i == 5 ? ft_strdup("and") : *operat);
    *operat = (i == 6 ? ft_strdup("or") : *operat);
    *operat = (i == 7 ? ft_strdup("xor") : *operat);
    *operat = (i == 8 ? ft_strdup("zjmp") : *operat);
    *operat = (i == 9 ? ft_strdup("ldi") : *operat);
    *operat = (i == 10 ? ft_strdup("sti") : *operat);
    *operat = (i == 11 ? ft_strdup("fork") : *operat);
    *operat = (i == 12 ? ft_strdup("lld") : *operat);
    *operat = (i == 13 ? ft_strdup("lldi") : *operat);
    *operat = (i == 14 ? ft_strdup("lfork") : *operat);
    *operat = (i == 15 ? ft_strdup("aff") : *operat);
}