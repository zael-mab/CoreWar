/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:48:04 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/20 18:01:56 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	read_set_data(t_asmdata *data, t_head *head, t_head_lb *labels)
{
	if (data->n == -1 && data->c == -1 && !check_champion_name_comment(data))
		return (0);
	if (data->n == -1 && data->c == -1)
		data->line = avoid_comment(data->line);
	if (data->n == -1 && data->c == -1 && ft_strlen(data->line))
		save_labels_and_commands(labels, ft_strtrim(data->line), head);
	if (!check_champion(data->line, data))
	{
		ft_printf("Error: Line num %d >>>%s.\n", data->ln, data->line);
		if (data->name)
			free(data->name);
		if (data->comment)
			free(data->comment);
		return (0);
	}
	return (1);
}

void	f_assembler(t_head *head, t_asmdata *data, int fd)
{
	t_head_lb	*labels;

	labels = (t_head_lb *)malloc(sizeof(t_head_lb));
	ft_bzero(labels, sizeof(t_head));
	data->ln = 0;
	while (get_next_line(fd, &data->line) > 0 && ++data->ln)
	{
		if (!(read_set_data(data, head, labels)))
		{
			if (data->line)
				free(data->line);
			free(data->file_name);
			free(labels);
			free(head);
			free(data);
			exit(0);
		}
		free(data->line);
	}
	if (head->first != NULL)
		assembly_to_bytecode(head, data, labels);
	else
		check_error(data, *labels, head);
	free(labels);
}

int	check_extention(char *line, t_asmdata *data)
{
	int			j;
	char		*tmp;

	j = ft_strlen(line);
	while (--j >= 0)
	{
		if (line[j] == '.' && line[j + 1] == 's' && line[j + 2] == '\0')
		{
			tmp = ft_strscpy(ft_strnew(j), line, 0, j + 1);
			data->file_name = ft_strjoin(tmp, ".cor");
			free(tmp);
			return (1);
		}
	}
	return (0);
}

int	main(int ac, char **av)
{
	int			fd;
	t_head		*head;
	t_asmdata	*sdata;

	if (ac == 2)
	{
		head = (t_head *)malloc(sizeof(t_head));
		ft_bzero(head, sizeof(t_head));
		sdata = (t_asmdata *)malloc(sizeof(t_asmdata));
		ft_bzero(sdata, sizeof(t_asmdata));
		fd = open(av[1], O_RDONLY);
		if (!check_extention(av[1], sdata))
			ft_printf("Error -file extention-\n");
		else
			f_assembler(head, sdata, fd);
		free(sdata);
		free(head);
		close(fd);
	}
	if (ac == 1)
		ft_printf("usage: ./asm file_name\n");
	if (ac > 2)
		ft_printf("Too many files!\n");
}
