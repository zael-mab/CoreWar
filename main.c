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


int main(int ac, char **av)
{
	if (ac == 2)
	{
		char 	*line;
		int 	fd;
		t_head 	head;
		t_head	labels;
		t_asmdata	sdata;

		ft_bzero (&head, sizeof (t_head)); 
		ft_bzero (&labels, sizeof (t_head));
		ft_bzero (&sdata, sizeof (t_asmdata));
		init_head (&head);
		init_head (&labels);

		// /////////////////////////////////////
		// int 	i;			// maybe I should use it !?!?! 
		// i = -1;
		// while (++i <= ft_strlen(av[1]))
		// {
		// 	if (av[1][i] == '.')
		// 		if (av[1][i + 1] != 's' || ft_strlen(av[1]) != i + 2)
		// 		{
		// 			ft_printf ("Error\n");
		// 			return (0);
		// 		}
		// }/////////////////////////////////

		fd = open(av[1], O_RDONLY);
		sdata.error = -1;
		while (get_next_line(fd, &line) > 0)
		{
			// line = ft_strtrim(line);
			if (sdata.n == -1 && sdata.c == -1)
				line = avoid_comment((line));							// avoid comment 

			if (ft_strlen(line) && sdata.n == -1 && sdata.c == -1)		//	avoid empty lines
				{
					// t_node *p = NULL;
					// insert_node (&head, ft_strtrim(line), -1);					//	insert eash line 
					save_labels(&labels, ft_strtrim(line), &head);
				}

			check_champion(line, &sdata);								// check and save the name & the comment

			// ft_printf ("%d, %d\n", sdata.n, sdata.c);
			// if (sdata.n == -1 && sdata.c == -1 && !sdata.p_ex_code)
				// sdata.p_ex_code = head.l_size + 1;



			free (line);
		}

		// ft_printf ("\t[%s] | [%s]\t %d\n", sdata.name, sdata.comment, sdata.p_ex_code);
		display_nodes (&head);
		close (fd);
	}
	
	if (ac == 1)
		ft_printf ("No file detected!\n");
	if (ac > 2)
		ft_printf ("Too many files!\n");
}


char 	*avoid_comment (char *line)				// deal with the comments  !!!
{
	int i;
	char *str;

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

