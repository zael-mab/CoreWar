/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:48:04 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/03 14:22:00 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
repeat.
read the next Assembly command
break it into the different fields it is composed of .
lookup the binary code for each field.
combine these code into a single machine language command.
output this machine language command.
*/

int				check_champion_name_comment(t_asmdata *data)
{
	if (data->comment && (ft_strlen(data->comment) > COMMENT_LENGTH))
	{
		ft_printf("Error: .comment too long (%d) > max len (%d)\n",
		ft_strlen(data->comment), COMMENT_LENGTH);
		free(data->comment);
		if (data->name)
			free(data->name);
		return (0);
	}
	if (data->name && (ft_strlen(data->name) > PROG_NAME_LENGTH))
	{
		ft_printf("Error: .comment too long (%d) > max len (%d)\n",
		ft_strlen(data->name), PROG_NAME_LENGTH);
		free(data->name);
		if (data->comment)
			free(data->comment);
		return (0);
	}
	return (1);
}

int				read_set_data(t_asmdata *data, t_head *head, t_head_lb *labels)
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
			free (data->name);
		if (data->comment)
			free (data->comment);
		return (0);
	}
	return (1);
}


void			check_error(t_asmdata *data, t_head_lb labels, t_head *head)
{
	if (data->ln == 1)
		ft_printf ("Empty file\n");
	else if (data->n != -1)
	{
		free(data->comment);
		ft_printf("Error: no Name!\n");
	}
	else if (data->c != -1)
	{
		free(data->name);
		ft_printf("Error: no Comment\n");
	}
	else
	{
		free(data->name);
		free(data->comment);
		ft_printf("ERROR: Champ has no instructions!\n");
	}
	if (labels.first != NULL)
		list_del_all_lb(&labels);
	if (head->first != NULL)
		list_del_all(head);
	free(data->file_name);
}

void			f_assembler(t_head *head, t_asmdata *data, int fd)
{
	t_head_lb	labels;

	ft_bzero(&labels, sizeof(t_head));
	data->ln = 0;
	while (get_next_line(fd, &data->line) > 0 && ++data->ln)
	{
		if (!(read_set_data(data, head, &labels)))
		{
			if (data->line)
				free(data->line);
			exit(0);
		}
		free(data->line);
	}
	if (head->first != NULL)
		assembly_to_bytecode(head, data, &labels);
	else
		check_error(data, labels, head);
}

int				check_extention(char *line, t_asmdata *data)
{
	int			j;
	char		*tmp;

	j = ft_strlen(line);
	while (--j >= 0)
		if (line[j] == '.')
			if (line[j + 1] == 's' && line[j + 2] == '\0')
			{
				tmp = ft_strscpy(ft_strnew(j), line, 0, j + 1);
				data->file_name = ft_strjoin(tmp, ".cor");
				free(tmp);
				return (1);
			}
	return (0);
}

int				main(int ac, char **av)
{
	int			fd;
	t_head		head;
	t_asmdata	sdata;

	if (ac == 2)
	{
		ft_bzero(&head, sizeof(t_head));
		ft_bzero(&sdata, sizeof(t_asmdata));
		fd = open(av[1], O_RDONLY);
		sdata.error = -1;
		if (!check_extention(av[1], &sdata))
		{
			ft_printf("Error -file extention-\n");
			exit(0);
		}
		f_assembler(&head, &sdata, fd);
		close(fd);
	}
	if (ac == 1)
		ft_printf("Syntax error at token [TOKEN][001:001] END (null)!\n");
	if (ac > 2)
		ft_printf("Too many files!\n");
}
