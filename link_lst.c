/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 link_lst.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: zael-mab <zael-mab@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/02/02 15:32:58 by zael-mab		   #+#	  #+#			  */
/*	 Updated: 2021/02/02 18:25:05 by zael-mab		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "asm.h"

void	*list_get(t_head *head)
{
	t_node	*l;
	char	*data;
	int		i;

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

void	list_del_all (t_head *head)
{
	while (head->first != NULL)
		list_get(head);
}

void	*list_get_lb(t_head_lb *head)
{
	t_label		*l;
	char		*data;

	if (head->first == NULL)
		return (NULL);
	l = head->first;
	data = l->data;
	head->first = head->first->next;
	head->l_size--;
	free(l->data);
	free(l);
	return (data);
}

void	list_del_all_lb(t_head_lb *head)
{
	while (head->first != NULL)
		list_get_lb(head);
}

t_node	*insert_node(t_head *head, void *data)
{
	t_node	*new_node;
	t_node	*p;

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
	if (new_node->position + 1 == head->l_size)
		return (new_node);
	return (NULL);
}

t_label	*insert_label(t_head_lb *head, void *data, int pos)
{
	t_label	*new_node;
	t_label	*p;

	new_node = ft_memalloc (sizeof (t_label));
	new_node->data = ft_strdup(data);
	new_node->size_ind = -1;
	new_node->operation_num = pos;
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
	if (new_node->position + 1 == head->l_size)
		return (new_node);
	return (NULL);
}

t_label	*search_by_name(t_label *l, char *x)
{
	if (l == NULL)
		return (NULL);
	if (!ft_strcmp(l->data, x))
		return (l);
	else
		return (search_by_name(l->next, x));
}

t_label	*search_by_pos(t_label *l, size_t x)
{
	if (l == NULL)
		return (NULL);
	if (l->operation_num == x)
		return (l);
	else
		return (search_by_pos(l->next, x));
}

int	check_isdigit(char *tmp, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		if (ft_isdigit(tmp[i]) || tmp[i] == 95
			|| (tmp[i] >= 97 && tmp[i] <= 122))
			i++;
		else
			break ;
	}
	return (i);
}
