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
    char    *t;

    tmp = ft_strnew(ft_strlen(line));
    if (sdata->x == 0)
    {
        *cmd = ft_strcpy (ft_strnew(v), line + sdata->s);
        t = ft_strjoin (*cmd, "\n");
        free (*cmd);
        *cmd = t;
    }
    if (sdata->x > 0 && !sdata->e)
    {
        t = ft_strjoin (*cmd, line);
        free (*cmd);
        *cmd = ft_strjoin (t, "\n");
        free(t);
    }
    if (sdata->x > 0 && sdata->e)
    {
        t = ft_strjoin(*cmd, ft_strscpy(tmp, line, 0, sdata->e));
        free (*cmd);
        *cmd = t;
        sdata->x = -1;
        sdata->c = (sdata->c == 1 ? -1 : sdata->c);
        sdata->n = (sdata->n == 1 ? -1 : sdata->n);
    }
    free (tmp);
    return (1);
}

int         pars_chmp_nm_cm(t_asmdata *data, char *line)
{
    char *tmp;

    tmp = avoid_comment(ft_strtrim(data->e + line));
    if (data->e > 0 && (data->n == 1 || data->c == 1) && ft_strlen(tmp) != 0)
    {
        free (tmp);
        data->error = 1;
        return (0);
    }
    free (tmp);
    
    if (data->n == 1 && data->s && data->e && data->x == -1)
        if ((data->name = ft_strscpy(ft_strnew(PROG_NAME_LENGTH), line, data->s, data->e)))
            data->n = -1;
    if (data->c == 1 && data->s && data->e && data->x == -1)
        if((data->comment = ft_strscpy(ft_strnew(COMMENT_LENGTH), line, data->s, data->e)))
            data->c = -1;
    if (data->s && (data->c == 1 || data->n == 1))
    {
        data->x++;
        if (data->n == 1)
            return (join(line, data, &data->name, PROG_NAME_LENGTH));
        if (data->c == 1)
            return (join (line, data, &data->comment, COMMENT_LENGTH));
    }
    return(1);
}

int         search_for_exention(char *line, t_asmdata *data, int j)
{
    while (line[++j])
        if (line[j] != ' ' && line[j] != '\t')
            break;
    if (line[j] == '.')
    {
        if (ft_strscmp(NAME_CMD_STRING, j + line, 0, 5) == 0 || ft_strscmp(COMMENT_CMD_STRING, j + line, 0, 8) == 0)
        {
            if (data->s && !data->e)
                return (-1);
            data->e = 0;
            data->s = 0;
            data->x = -1;
            data->n = (ft_strscmp(NAME_CMD_STRING, j + line, 0, 5) == 0) ? 1 : data->n;
            data->c = (ft_strscmp(COMMENT_CMD_STRING, j + line, 0, 8) == 0) ? 1 : data->c;
            j = (data->n == 1 ? j + 4 : j);
            j = (data->c == 1 ? j + 7 : j);
            return (j);
        }
        data->error = 1;
    }
    return (-1);
}

int         check_champion (char *line, t_asmdata *sdata)
{
    int     j;

    j = -1;
    j = search_for_exention(line, sdata, j);
    if (sdata->n != 1 && sdata->c != 1)
        return (1);
    while (line[++j])
    {
        if (line[j] != ' ' && line[j] != '\t' && line[j] != '"' && sdata->x == -1 && !sdata->s)
            return (0);
        if (line[j] == '"' && sdata->s && !sdata->e)
            sdata->e = j + 1;
        if (line[j] == '"' && !sdata->s)
            sdata->s = j + 1;
    }
    return (pars_chmp_nm_cm(sdata, line));
}