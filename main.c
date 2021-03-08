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

// ////////////////////////			CHECK THE .s extend
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
			

			if (sdata.n == -1 && sdata.c == -1)		//	avoid empty lines
					save_labels(&labels, ft_strtrim(line), &head);		//	labels and instrucions

			int n = 0;
			while (line[++n] && line[n] != '.');
			if (n == ft_strlen(line))
				n = 0;
			// else
				// n++;
			if (!check_champion(n + line, &sdata))								// check and save the name & the comment
			{
				perror("incorect file\n");			// don't forget to free;
				exit(1);
			}

			free (line);
			ln++;									// I'll need ya later.
		}

		ft_printf ("\t[%s] | [%s]\t %d\n", sdata.name, sdata.comment, sdata.p_ex_code);
// ////////////////////////////////////////
		if (ln == 0)
		{
			list_del_all(&head);
			list_del_all(&labels);
			ft_printf ("empty file\n");
			exit (1);
		}
		ft_printf("-------%s\n", line);
		// if (ft_strlen(sdata.name) > PROG_NAME_LENGTH || ft_strlen(sdata.comment) > COMMENT_LENGTH)
		// {
		// 	list_del_all(&head);
		// 	list_del_all(&labels);
		// 	ft_printf ("~0*~~~~~~~~Error length~~~~~~~~|%d|%d|\n", ft_strlen(sdata.name), ft_strlen(sdata.comment));
		// 	exit (0);
		// }
		if (sdata.n != -1 || sdata.c != -1)
		{
			list_del_all(&head);
			list_del_all(&labels);
			exit (0);
		}


///////////////***********///////////
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

		if (!set_label_args(&head, labels, &sdata))
		{
			list_del_all(&head);
			list_del_all(&labels);
			exit (0);
		}
		// display_nodes (&head);
		int fp;
		int jumper;
		int c;

		fp = open ("test.cor", O_CREAT | O_RDWR, 0600);					//CHANGE THE NAME OF THE FILE !!!
		jumper = -1;
		
		
		// hold = (char *)reverse_endian(COREWAR_EXEC_MAGIC);
		int y = reverse_endian(COREWAR_EXEC_MAGIC);
		write (fp, &y, 4);												// revers the magic_code and print it as a hex

		jumper = -1;
		while (sdata.name[++jumper] && write (fp, &sdata.name[jumper], 1));	// print the name

		c = PROG_NAME_LENGTH - ft_strlen(sdata.name) + 4;
		lseek(fp, c * sizeof (char), SEEK_END);

		y = reverse_endian(head.code_size);							// revers the code_size and print it.
		write(fp, &y, 4);

	
		jumper = -1;
		while (sdata.comment[++jumper] && write (fp, &sdata.comment[jumper], 1));	// print the comment
		c = COMMENT_LENGTH - ft_strlen(sdata.comment) + 4;
		lseek(fp, c * sizeof (char), SEEK_END);
		

		decode(&sdata, &head, fp);

		// ft_printf ("Writing output program to %s\n", corfile);
/////////////////////////////////////////////////////


		// ft_printf ("\t----------\n");
		// display_nodes (&labels);
		// ft_printf ("\t----------\n");
		// display_nodes (&head);
		// ft_printf ("\t-----*----\n\n");
	
		close (fd);
		close (fp);
	}
	
	if (ac == 1)
		ft_printf ("Syntax error at token [TOKEN][001:001] END (null)!\n");
	if (ac > 2)
		ft_printf ("Too many files!\n");
}



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
