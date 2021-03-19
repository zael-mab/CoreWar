/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 xxx.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: zael-mab <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/03/12 15:42:30 by zael-mab		   #+#	  #+#			  */
/*	 Updated: 2021/03/19 16:23:26 by zael-mab		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "asm.h"

int	reverse_endian(int i)
{
	unsigned char	c1;
	unsigned char	c2;
	unsigned char	c3;
	unsigned char	c4;

	c1 = i;
	c2 = i >> 8;
	c3 = i >> 16;
	c4 = i >> 24;
	return (((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4);
}

int	get_labels_value(t_label *l, t_node *instru, t_label *first, int counter)
{
	int				jumper;
	char			*tmp;

	l = NULL;
	jumper = -1;
	while (++jumper < instru->arg_num)
	{
		if ((instru->lb & jumper + 1 && jumper != 2)
			|| (instru->lb & 4 && jumper == 2))
		{
			tmp = ft_strtrim(1 + ft_strchr(instru->arg_tab[jumper], LABEL_CHAR));
			l = search_by_name(first, tmp);
			if (l)
			{
				free (tmp);
				if (l->size_ind == -1)
				{
					ft_printf ("Error: label '%s' points to nothing.\n", l->data);
					return (0);
				}
				instru->arg[jumper] = l->size_ind - counter;
			}
		}
	}
	return (1);
}

int	set_label_args(t_head *head, t_head_lb labels, t_asmdata *data)
{
	t_label		*l;
	t_node		*instru;
	int			counter;

	instru = head->first;
	l = labels.first;
	counter = 0;
	while (instru)
	{
		if (instru->lb > 0 && !get_labels_value(l, instru, labels.first, counter))
		{
			data->error += 16;
			return (0);
		}
		counter += instru->command_size;
		data->y = 0;
		instru = instru->next;
	}
	return (1);
}

void	assembly_to_bytecode(t_head *head, t_asmdata *data, t_head_lb *labels)
{
	if (!pars_instructions(head, *labels, data)
		|| !set_label_args(head, *labels, data))
	{
		if (data->error & 16)
			ft_printf ("Error\n");
	}
	if (head->code_size != 0 && data->error == 0)
		to_byte_code(head, data);
	free (data->name);
	free (data->comment);
	free (data->file_name);
	if (labels->first != NULL)
		list_del_all_lb(labels);
	if (head->first != NULL)
		list_del_all(head);
}

int	save_labels_and_commands(t_head_lb *labels, char *line, t_head *head)
{
	int			j;
	char		*tmp;
	static int	tmp_post;
	t_node		marker;
	t_label		l;

	j = -1;
	while (line[++j])
		if (line[j] == LABEL_CHAR)
			break ;
	tmp = ft_strncpy(ft_strnew(j), line, j);
	if (ft_strlen(line) > j)
	{
		if (j == check_isdigit(tmp, j))
		{
			if (ft_strlen(line) > j + 1)
			{
				marker = *insert_node(head, ft_strtrim (j + 1 + line));
				l = *insert_label(labels, tmp, tmp_post);
				tmp_post = marker.position + 1;
			}
			else
				l = *insert_label(labels, tmp, tmp_post);
			free (tmp);
			free (line);
			return (1);
		}
	}
	free (tmp);
	marker = *insert_node (head, line);
	tmp_post = marker.position + 1;
	return (1);
}
