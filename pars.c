/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <zael-mab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 11:48:24 by zael-mab          #+#    #+#             */
/*   Updated: 2021/02/03 14:22:42 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
/*
name;
Comment;
Executable code;

             FOR PARS:
in one line - one instruction. "sequence of instructions"
     Empty lines, comments, as well as extra tabs or spaces are ignored.

verything between the character '#' and the end of the line is considered a comment. 

An empty string is a valid champion name : [ .name "" ]
     but But lack of the string is an error: [ .name  ] (same case for the comment)

Also, in the file .s must be present champion's comment.

the command  " .extend " -and all other commands excepting '.name' and '.comment'- detected as an error

                 FOR EXUECUTABLE CODE:
 Assembly language has a rule one instruction per line. The new line character \n means both end
      of line and end of instruction. So instead of ; as for C language, we will use \n.

     Each redcode instruction contains 3 parts : Opcode itself, the source address A-field 
         and the destination address B-field.
*/


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

int         join (char *line, t_asmdata *sdata, char **cmd, int v)
{
    char    *tmp;

    tmp = ft_strnew(ft_strlen(line));
    if (sdata->error == 0)
    {
        *cmd = ft_strjoin (ft_strnew(v), line + sdata->s);
        *cmd = ft_strjoin (*cmd, "\n");
    }
    if (sdata->error > 0 && !sdata->e)
    {
        *cmd = ft_strjoin (*cmd, line);
        *cmd = ft_strjoin (*cmd, "\n");
    }
    if (sdata->error > 0 && sdata->e)
    {
        *cmd = ft_strjoin(*cmd, ft_strscpy(tmp, line, 0, sdata->e));
        sdata->error = -1;
        sdata->c = (sdata->c == 1 ? -1 : sdata->c);
        sdata->n = (sdata->n == 1 ? -1 : sdata->n);
    }
    free (tmp);
    return (1);
}

int         pars_chmp_nm_cm(t_asmdata *sdata, char *line)
{
    if (sdata->e > 0 && (sdata->n == 1 || sdata->c == 1) && ft_strlen(ft_strtrim(sdata->e + line)) != 0) // check the restof line "something"x
    {
        ft_printf("#Error in the line[%s] \n", line);
        return (0);
    }
    if (sdata->n == 1 && sdata->s && sdata->e && sdata->error == -1)
        if ((sdata->name = ft_strscpy(ft_strnew(PROG_NAME_LENGTH), line, sdata->s, sdata->e)))
            sdata->n = -1;
    if (sdata->c == 1 && sdata->s && sdata->e && sdata->error == -1)
        if((sdata->comment = ft_strscpy(ft_strnew(COMMENT_LENGTH), line, sdata->s, sdata->e)))
            sdata->c = -1;

    if (sdata->s && (sdata->c == 1 || sdata->n == 1))
    {
        sdata->error++;
        if (sdata->n == 1)
            join(line, sdata, &sdata->name, PROG_NAME_LENGTH);
        if (sdata->c == 1)
            join (line, sdata, &sdata->comment, COMMENT_LENGTH);
        return (1);
    }
    return(1);
}

int         search_for_exention(char *line, t_asmdata *data)
{
    int j;

    j = -1;
    while (line[++j])
        if (line[j] == '.' && ((ft_strscmp(NAME_CMD_STRING, j + line, 0, 5) == 0)
        || ft_strscmp(COMMENT_CMD_STRING, j + line, 0, 5) == 0))
        {
            data->e = 0;
            data->s = 0;
            data->error = -1;
            return (j);
        }
    return (-1);
}

int         check_champion (char *line, t_asmdata *sdata)
{
    int     j = 0;

    j = search_for_exention(line, sdata);
    sdata->n = (ft_strscmp(NAME_CMD_STRING,j + line, 0, 5) == 0) ? 1 : sdata->n;
    sdata->c = (ft_strscmp(COMMENT_CMD_STRING,j + line, 0, 8) == 0) ? 1 : sdata->c;
    j = -1;
    while (line[++j])
    {
        if (line[j] == '"' && sdata->s && !sdata->e)
            sdata->e = j + 1;
        if (line[j] == '"' && !sdata->s)
            sdata->s = j + 1;
    }
    if (!(pars_chmp_nm_cm(sdata, line)))
        return (0);
    return (1);
}