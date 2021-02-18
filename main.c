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
		t_asmdata	sdata;

		ft_bzero (&head, sizeof (t_head));
		ft_bzero (&sdata, sizeof (t_asmdata));
		init_head (&head);

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
			if (sdata.name && sdata.comment)
				line = avoid_comment((line));		// avoid comment 

			// if (!sdata.name || !sdata.comment)
			check_champion(line, &sdata);			// check and save the name & the comment

			if (sdata.name && sdata.comment && !sdata.p_ex_code)
				sdata.p_ex_code = head.l_size + 1;

			if (ft_strlen(line) && sdata.name)					//	avoid empty lines
				insert_node (&head, ft_strtrim(line));				//	insert eash line 

			// ft_printf ("%s\n", line);

			free (line);
		}

		ft_printf ("\t[%s] | [%s]\n\t %d\n", sdata.name, sdata.comment, sdata.error);
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

