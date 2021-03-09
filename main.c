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

// repeat.
// read the next Assembly command
// break it into the different fields it is composed of .
// lookup the binary code for each field.
// combine these code into a single machine language command.
// output this machine language command.
void 	xxx(t_head *head, t_asmdata *data, t_head *labels, int ln); // CHANGE THE NAME


/////////////////////////////////////////////////
int 				main(int ac, char **av)
{
	if (ac == 2)
	{
		int 		fd;
		t_head 		head;
		t_asmdata	sdata;

		ft_bzero (&head, sizeof (t_head)); 
		ft_bzero (&sdata, sizeof (t_asmdata));
		fd = open(av[1], O_RDONLY);
		sdata.error = -1;
		if (!check_extention(av[1], &sdata))
		{
			ft_printf("Error -file extention-\n");
			exit (0);
		}
		f_assembler(&head, &sdata, fd);
		close (fd);
	}
	if (ac == 1)
		ft_printf ("Syntax error at token [TOKEN][001:001] END (null)!\n");
	if (ac > 2)
		ft_printf ("Too many files!\n");
}


//norme
void			f_assembler (t_head *head, t_asmdata *data, int fd)
{
	t_head		labels;
	char 		*line;
	int 		ln;
	int 		n;

	ft_bzero (&labels, sizeof (t_head));
	ln = 0;
	while (get_next_line(fd, &line) > 0 && ++ln)
	{
		if (data->n == -1 && data->c == -1)
			line = avoid_comment(line);							// avoid comment 
		if (data->n == -1 && data->c == -1)		//	avoid empty lines
			save_labels(&labels, ft_strtrim(line), head);		//	labels and instrucions
		n = -1;

		while (line[++n] && line[n] != '.' && (data->n != -1 || data->c != -1));
		if (n == ft_strlen(line))
			n = 0;
		if (!check_champion(n + line, data))								// check and save the name & the comment
		{
			perror("incorect file\n");			// don't forget to free;
			exit(1);
		}
		free (line);
	}
	xxx (head, data, &labels, ln - 1);
}


//norme
void 	xxx(t_head *head, t_asmdata *data, t_head *labels, int ln) // CHANGE THE NAME
{
	if (ln == 0)
	{
		list_del_all(head);
		list_del_all(labels);
		ft_printf ("empty file\n");
		exit (1);
	}
	if (data->n != -1 || data->c != -1)
	{
		list_del_all(head);
		list_del_all(labels);
		exit (0);
	}
	if (!pars_instructions(head, *labels, data))
	{
		list_del_all(head);
		list_del_all(labels);
		exit (0);
	}
	if (!set_label_args(head, *labels, data))
	{
		ft_printf("labels\n");
		list_del_all(head);
		list_del_all(labels);
		exit (0);
	}
	to_byte_code(head, data);
	list_del_all(head);
	list_del_all(labels);
}

///////////////////////////////////////////
int 				reverse_endian (int i)
{
    unsigned char	c1;
	unsigned char	c2;
	unsigned char	c3;
	unsigned char	c4;

	c1 = i;
	c2 = i >> 8;
	c3 = i >> 16;
	c4 = i >> 24;
	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

///////////////////////////////////////////
char 		*avoid_comment (char *line)				// deal with the comments  !!!
{
	int 	i;
	char 	*str;

	i = -1;
	while (line[++i])
	{
		if (line[i] == COMMENT_CHAR || line[i] == ALT_COMMENT_CHAR)
		{
			str = ft_strncpy(ft_strnew (i), line, i);
			free (line);
			return (str);
		}
	}
	return (line);
}

///////////////////////////////////////////
int			check_extention(char *line, t_asmdata *data)
{
	int 	j;

	j = ft_strlen(line);
	while (--j >= 0)
		if (line[j] == '.')
		{
			if (line[j + 1] == 's' && line[j + 2] == '\0')
			{
				data->file_name = ft_strjoin(ft_strscpy(ft_strnew(j), line, 0, j + 1) , ".cor");
				return (1);
			}
			else
				return (0);
		}
	return (0);
}