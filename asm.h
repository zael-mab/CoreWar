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

typedef enum {F , T}    boolean;

typedef struct      s_node
{
    void            *data;
    size_t          position;
    struct s_node   *next;
}                   t_node;

typedef struct      s_head
{
    size_t          l_size;
    struct s_node   *first;
}                   t_head;

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
}                   t_asmdata;

boolean     insert_node(t_head *head, void    *data);
void        display_nodes(t_head *first);
void        init_head(t_head *head);
char 	    *avoid_comment (char *line);
boolean     check_champion (char *line, t_asmdata *sdata);
boolean     join (char *line, t_asmdata *sdata, char **cmd, int v);
t_node      *search(t_node *l, void* x);



# endif
