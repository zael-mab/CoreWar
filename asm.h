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
    
    int             arg_num;
    int             encodin_code;
    int             encodin;
    
    int             operation_num;          //labels -pointes operation-. (need to calculate the number of bytes btween the arg_label and the instruction tha label pointed to)
    int             size_ind;
    
    int             op_code;                //num of operater.
    int             w_args[9];                // what arg.
    int             lb;
    
    int             arg[3];  
    char            **arg_tab;           
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
    char            *file_name;
    int             n;
    int             c;
    int             s;
    int             e;
    int             error;
    char            **op_args;            //split the args[arg_num]!!
    int             p_ex_code;
    int             x;
    int             y;
}                   t_asmdata;

t_op            g_op_tab[17];




void        display_nodes(t_head *head);       // DELETE 
void        init_head(t_head *head);            //DELETE

char 	    *avoid_comment (char *line);
int			check_extention(char *line, t_asmdata *data);
int         pars_chmp_nm_cm(t_asmdata *sdata, char *line);
int         check_champion (char *line, t_asmdata *sdata);
int         join (char *line, t_asmdata *sdata, char **cmd, int v);

t_node      *insert_node(t_head *head, void    *data, int pos);
t_node      *save_labels(t_head *labels, char *lin, t_head *head);

t_node      *search_by_pos(t_node *l, int x);
t_node      *search_by_name(t_node *l, char* x);




int         pars_instructions(t_head *head, t_head labels, t_asmdata *sdata);

void        operations(char **operat, int i);

int         check_isdigit(char *tmp, int j);
int         pars_args(t_node *instruction, t_asmdata *sdata, int y, t_head labels);

int         reg_lexical_analysis (t_asmdata *data, t_node *instruction, int y);
int         dirl_lexical_analysis (t_asmdata *data, t_node *instruction,t_head labels, int y, int x);
int         dir_lexical_analysis (t_asmdata *data, t_node *instruction, int y, int x);
int         ind_lexical_analysis (t_asmdata *data, t_node *instruction,t_head labels, int y, int x);


int         check_oper(t_node *instruct, t_head labels, t_head *head, t_asmdata *data);
int         check_dir_lebel(char *line, int arg, t_head labels);
int         check_dir(char *line, int arg, t_node *instr, t_asmdata data);
int         check_ind(char *line, int arg, t_head labels);

int         check_reg(char *line, int arg, t_node *instru, t_asmdata data);


void        *list_get(t_head *head);
void        list_del_all (t_head *head);

void        to_byte_code(t_head *head, t_asmdata *data);

int         reverse_endian (int i);
void        decode(t_asmdata *data, t_head *cmmnd, int fd);
void        add_encodin_code(t_asmdata *sdata, t_node *instruct);
void        init_encodin_byte(t_node *instr, int p, int shift);

void        writ_args(t_asmdata *data, t_node *cmd, int fd);
int         set_label_args(t_head *head, t_head labels, t_asmdata *data);

void        get_labels_value(t_node *l, t_node *instru, t_node *first, int counter);
void			f_assembler (t_head *head, t_asmdata *data, int fd);




# endif
