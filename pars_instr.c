/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 pars_instr.c										:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: zael-mab <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/03/19 18:54:50 by zael-mab		   #+#	  #+#			  */
/*	 Updated: 2021/03/19 18:54:50 by zael-mab		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "asm.h"

void	add_encodin_code(t_asmdata *sdata, t_node *instruct)
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

void	init_encodin_byte(t_node *instr, int p, int shift)
{
	if (instr->w_args[p] == REG_CODE)
		instr->encodin += REG_CODE << shift;
	if (instr->w_args[p] == DIR_CODE)
		instr->encodin += DIR_CODE << shift;
	if (instr->w_args[p] == IND_CODE)
		instr->encodin += IND_CODE << shift;
}

int	check_oper(t_node *instr, t_head_lb labels, t_head *head, t_asmdata *data)
{
	int		x;
	char	*tmp;

	tmp = ft_strncpy(ft_strnew(5), instr->data, data->x);
	x = -1;
	while (++x < 17)
	{
		if (!ft_strcmp(tmp, g_op_tab[x].name))
		{
			search_for_labels_init(labels, instr, head);
			if (!pars_args(instr, data, x, labels))
			{
				free(tmp);
				return (-1);
			}
			instr->command_size += 1;
			if (x == 17)
				instr->code = -1;
			else
				instr->code = g_op_tab[x].op_code;
			instr->arg_num = g_op_tab[x].args_numb;
			instr->encodin_code = g_op_tab[x].encoding_code;
			if (instr->encodin_code > 0)
				add_encodin_code(data, instr);
			break ;
		}
	}
	free(tmp);
	return (x);
}

void	search_for_labels_init(t_head_lb labels, t_node *instr, t_head *head)
{
	t_label	*l;

	l = search_by_pos(labels.first, instr->position);
	if (l && l->size_ind == -1)
		l->size_ind = instr->command_size + head->code_size;
	if (l && l->next != NULL)
	{
		while (l)
		{
			if (l->operation_num == instr->position && l->size_ind == -1)
				l->size_ind = instr->command_size + head->code_size;
			l = l->next;
		}
	}
}

int			xxxx(t_asmdata *data, t_node *instruct, t_head_lb labels, t_head *head);

int			pars_instructions(t_head *head, t_head_lb labels, t_asmdata *sdata)		  //REG_NUMBER
{
	t_node	*instruct;

	instruct = NULL;
	instruct = head->first;
	sdata->error = 0;
	while (instruct != NULL)
	{
		sdata->x = -1;
		while (instruct->data[++sdata->x])
			if (instruct->data[sdata->x] < 'a' || instruct->data[sdata->x] > 'z')
				break;
		if (!(xxxx(sdata, instruct, labels, head)))
			return (0);
		instruct = instruct->next;
	}
	return (1);
}


int			xxxx(t_asmdata *data, t_node *instruct, t_head_lb labels, t_head *head)
{
	int		x;

	if (data->x == 0 && ft_strlen (instruct->data) > 0)
		return (print_oper_error(instruct->data, data));
	if (data->x > 0)
	{
		x = check_oper(instruct, labels, head, data);
		if (x == 17)
			return (print_oper_error(instruct->data, data));
		if (x == -1)
			return (0);
		head->code_size += instruct->command_size;
	}
	return (1);
}
