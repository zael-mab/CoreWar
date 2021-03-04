/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 10:48:45 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/03 14:22:25 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// fix the ft_printf macros !
#ifndef ASM_H
#define ASM_H

#include "libft/libft.h"
#include "op.h"
#include<fcntl.h> 
#include<errno.h>
#include <stdio.h>

typedef enum {F , T}    boolean;

typedef struct      s_node
{
    char            *data;
    size_t          position;
    size_t          code;
    int             encodin_code;
    int             encodin;
    int             operation_num;          //labels -pointes operation-. (need to calculate the number of bytes btween the arg_label and the instruction tha label pointed to)
    int             op_code;                //num of operater.
    int             w_args[6];                // what arg.
    // char            op_args[3];            //split the args[number of args]!!
    size_t          command_size;
    struct s_node   *next;
}                   t_node;

typedef struct      s_head
{
    size_t          l_size;
    size_t             code_size;
    struct s_node   *first;
}                   t_head;


typedef struct 	s_op 
{
	char 		name[5];
	int 		args_numb;
	int			args[3];
	int 		op_code;
	int			wait_to_run;
	char		des[60];
	int			encoding_code;
	int			dir_size;
}				t_op;


typedef struct      s_asmdata
{
    char            *name;
    char            *comment;
    int             n;
    int             c;
    int             s;
    int             e;
    int             error;
    int             p_ex_code;
    int             x;
}                   t_asmdata;

t_op            g_op_tab[17];




t_node      *insert_node(t_head *head, void    *data, int pos);
void        display_nodes(t_head *head);       // DELETE 
void        init_head(t_head *head);            //DELETE
char 	    *avoid_comment (char *line);
boolean     check_champion (char *line, t_asmdata *sdata);
boolean     join (char *line, t_asmdata *sdata, char **cmd, int v);
t_node      *search(t_node *l, char* x);


t_node      *save_labels(t_head *labels, char *lin, t_head *head);

int         pars_instructions(t_head *head, t_head labels, t_asmdata *sdata);

void        operations(char **operat, int i);

int         pars_args(t_node *instruction, t_asmdata *sdata, int y, t_head labels);
int         check_dir_lebel(char *line, int arg, t_head labels);
int         check_dir(char *line, int arg);
int         check_ind(char *line, int arg, t_head labels);




void        *list_get(t_head *head);
void        list_del_all (t_head *head);
size_t      reverse_endian (size_t i);  // CHANGE it !!!

void        decode(t_asmdata *data, t_head *cmmnd, int fd);
# endif
