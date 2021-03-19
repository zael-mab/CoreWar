/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 args.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: zael-mab <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/02/21 17:44:27 by zael-mab		   #+#	  #+#			  */
/*	 Updated: 2021/02/21 17:44:35 by zael-mab		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "asm.h"

int	pars_args(t_node *instr, t_asmdata *data, int y, t_head_lb labels)
{
	int		c;
	char	*tmp;

	instr->arg_tab = ft_strsplit(data->x + instr->data, SEPARATOR_CHAR);
	data->op_tb = instr->arg_tab;
	c = 0;
	while (instr->data[++data->x])
		if (instr->data[data->x] == ',')
			c++;
	data->y = -1;
	while (data->op_tb[++data->y])
	{
		tmp = ft_strtrim(data->op_tb[data->y]);
		free(data->op_tb[data->y]);
		data->op_tb[data->y] = tmp;
		if (data->y == g_op_tab[y].args_numb && c + 1 > g_op_tab[y].args_numb)
			break ;
		if (!trt_arg(data, instr, labels, y))
			return (0);
	}
	if (data->y != g_op_tab[y].args_numb || c + 1 != g_op_tab[y].args_numb)
		return (print_arg_error(*instr, data, data->y,
				2 + (c + 1 > g_op_tab[y].args_numb)));
	instr->command_size += g_op_tab[y].encoding_code;
	return (1);
}

int	trt_arg(t_asmdata *data, t_node *instr, t_head_lb labels, int y)
{
	int		x;

	x = -1;
	if (ft_strlen(data->op_tb[data->y]) == 0)
		return (print_arg_error(*instr, data, data->y, 0));
	while (data->op_tb[data->y][++x])
	{
		if (data->op_tb[data->y][x] == 'r'
			&& ft_isdigit(data->op_tb[data->y][x + 1]))
			return (reg_lexical_analysis(data, instr, y));
		if (data->op_tb[data->y][x] == 'r'
			&& !ft_isdigit(data->op_tb[data->y][x + 1]))
			return (0);
		else if (data->op_tb[data->y][x] == '%'
			&& data->op_tb[data->y][x + 1] == ':')
			return (dirl_lexical_analysis(data, instr, labels, y, x));
		else if (data->op_tb[data->y][x] == '%')
			return (dir_lexical_analysis(data, instr, y, x));
		else if (data->op_tb[data->y][x] == '+'
			|| check_digit(data->op_tb[data->y]) || data->op_tb[data->y][x] == ':')
			return (ind_lexical_analysis(data, instr, labels, y, x));
		else
			return (print_arg_error(*instr, data, data->y, 0));
	}
	return (1);
}
