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
    size_t          code_size;
    struct s_node   *first;
}                   t_head;

typedef struct      s_label
{
    char            *data;
    size_t             operation_num;          //labels -pointes operation-. (need to calculate the number of bytes btween the arg_label and the instruction tha label pointed to)
    size_t          position;
    int             size_ind;
    struct s_label  *next;
}                   t_label;

typedef struct      s_head_lb
{
    size_t          l_size;
    size_t          code_size;
    struct s_label   *first;
}                   t_head_lb;

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
    char            *line;
    int             n;
    int             c;
    int             s;
    int             e;
    int             error;
    char            **op_args;            //split the args[arg_num]!!
    // int             p_ex_code;
    int             x;
    int             y;
}                   t_asmdata;


t_op                g_op_tab[17];

void        display_nodes(t_head *head);       // DELETE 
void        init_head(t_head *head);            //DELETE
////////////////////////
int			check_extention(char *line, t_asmdata *data);
void		f_assembler (t_head *head, t_asmdata *data, int fd);
int		    read_set_data(t_asmdata *data, t_head *head, t_head_lb *labels);
int			check_champion_name_comment(t_asmdata data);
//////////////////////

/////////////////////
char 	    *avoid_comment (char *line);
t_node      *save_labels_and_commands(t_head_lb *labels, char *lin, t_head *head);
/////////////////////
int         check_champion (char *line, t_asmdata *sdata);
int         search_for_exention(char *line, t_asmdata *data);
int         pars_chmp_nm_cm(t_asmdata *sdata, char *line);
int         join (char *line, t_asmdata *sdata, char **cmd, int v);
/////////////////////
void 	    assembly_to_bytecode(t_head *head, t_asmdata *data, t_head_lb *labels, int ln); // CHANGE THE NAME
int         pars_instructions(t_head *head, t_head_lb labels, t_asmdata *sdata);
int         set_label_args(t_head *head, t_head_lb labels, t_asmdata *data);
int         get_labels_value(t_label *l, t_node *instru, t_label *first, int counter);
int         check_digit(char *line);
/////////////////////////
int         reverse_endian (int i);
void        to_byte_code(t_head *head, t_asmdata *data);
void        decode(t_asmdata *data, t_head *cmmnd, int fd);
void        writ_args(t_asmdata *data, t_node *cmd, int fd);
//////////////////////////////////////
int         check_oper(t_node *instruct, t_head_lb labels, t_head *head, t_asmdata *data);
int         pars_args(t_node *instruction, t_asmdata *sdata, int y, t_head_lb labels);
int         trt_arg(t_asmdata *data, t_node *instruction, t_head_lb labels, int j, int y);
void        add_encodin_code(t_asmdata *sdata, t_node *instruct);
void        init_encodin_byte(t_node *instr, int p, int shift);
////////////////////////////
int         reg_lexical_analysis (t_asmdata *data, t_node *instruction, int y);
int         dirl_lexical_analysis (t_asmdata *data, t_node *instruction,t_head_lb labels, int y, int x);
int         dir_lexical_analysis (t_asmdata *data, t_node *instruction, int y, int x);
int         ind_lexical_analysis (t_asmdata *data, t_node *instruction,t_head_lb labels, int y, int x);
//////////////////////////////
int         check_reg(char *line, int arg, t_node *instru, t_asmdata data);
int         check_dir_lebel(char *line, int arg, t_head_lb labels);
int         check_dir(char *line, int arg, t_node *instr, t_asmdata data);
int         check_ind(char *line, int arg, t_head_lb labels);
int         check_isdigit(char *tmp, int j);
//////////////////////////////////////


///////////////////
t_label     *insert_label(t_head_lb *head, void    *data, int pos);
t_node      *insert_node(t_head *head, void    *data);
t_label      *search_by_pos(t_label *l, size_t x);
t_label      *search_by_name(t_label *l, char* x);
///////////////////









void        operations(char **operat, int i);







void        *list_get(t_head *head);
void        list_del_all (t_head *head);

void    *list_get_lb(t_head_lb *head);
void    list_del_all_lb (t_head_lb *head);






# endif
