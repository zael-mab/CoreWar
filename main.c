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
		char 		*line;
		int 		fd;
		int 		ln;
		t_head 		head;
		t_head		labels;
		t_asmdata	sdata;

		ft_bzero (&head, sizeof (t_head)); 
		ft_bzero (&labels, sizeof (t_head));
		ft_bzero (&sdata, sizeof (t_asmdata));

// ////////////////////////
		fd = open(av[1], O_RDONLY);
		sdata.error = -1;

		
		ln = 0;
		while (get_next_line(fd, &line) > 0)
		{
			// tmp = ft_strtrim(line);
			// free (line);
			// line = tmp;

			if (sdata.n == -1 && sdata.c == -1)
				line = avoid_comment(line);							// avoid comment 
			
			// ft_printf("-------%s\n", line);

			if (sdata.n == -1 && sdata.c == -1)		//	avoid empty lines
					save_labels(&labels, ft_strtrim(line), &head);

			check_champion(line, &sdata);								// check and save the name & the comment

			free (line);
			ln++;									// I'll need ya later.
		}

// ////////////////////////////////////////
		if (ln == 0)
		{
			list_del_all(&head);
			list_del_all(&labels);
			ft_printf ("empty file\n");
			exit (1);
		}
		if (ft_strlen(sdata.name) > PROG_NAME_LENGTH || ft_strlen(sdata.comment) > COMMENT_LENGTH)
		{
			list_del_all(&head);
			list_del_all(&labels);
			ft_printf ("~0*~~~~~~~~Error length~~~~~~~~|%d|%d|\n", ft_strlen(sdata.name), ft_strlen(sdata.comment));
			exit (0);
		}
		if (sdata.n != -1 || sdata.c != -1)
		{
			list_del_all(&head);
			list_del_all(&labels);
			ft_printf ("~0~~~~~~~~Error~~~~~~~~|%d|%d|\n", sdata.c, sdata.n);
			exit (0);
		}


///////////////***********///////////
		ft_printf ("\t[%s] | [%s]\t %d\n", sdata.name, sdata.comment, sdata.p_ex_code);
		// ft_printf ("\t----------\n");
		// display_nodes (&labels);
		// ft_printf ("\t----------\n");
		// display_nodes (&head);
		// ft_printf ("\t-----*----\n\n");
/////////////***********///////////

		if (!pars_instructions(&head, labels, &sdata))
		{
			list_del_all(&head);
			list_del_all(&labels);
			exit (0);
		}

		display_nodes (&head);

		// decode_to_byte_code();
		// ft_printf ("Writing output program to %s\n", corfile);
/////////////////////////////////////////////////////

		ft_printf ("\n\n%x\n", COREWAR_EXEC_MAGIC);
		close (fd);
	}
	
	if (ac == 1)
		ft_printf ("Syntax error at token [TOKEN][001:001] END (null)!\n");
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
