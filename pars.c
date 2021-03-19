/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 pars.c												:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: zael-mab <zael-mab@student.42.fr>			+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2021/01/26 11:48:24 by zael-mab		   #+#	  #+#			  */
/*	 Updated: 2021/03/19 18:35:57 by zael-mab		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include "asm.h"

char	*avoid_comment(char *line)
{
	int		i;
	char	*str;

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

int	join(char *line, t_asmdata *sdata, char **cmd, int v)
{
	char	*tmp;
	char	*t;

	tmp = ft_strnew(ft_strlen(line));
	if (sdata->x == 0)
	{
		*cmd = ft_strcpy(ft_strnew(v), line + sdata->s);
		t = ft_strjoin(*cmd, "\n");
		free(*cmd);
		*cmd = t;
	}
	if (sdata->x > 0 && !sdata->e)
	{
		t = ft_strjoin (*cmd, line);
		free(*cmd);
		*cmd = ft_strjoin (t, "\n");
		free(t);
	}
	if (sdata->x > 0 && sdata->e)
	{
		t = ft_strjoin(*cmd, ft_strscpy(tmp, line, 0, sdata->e));
		free(*cmd);
		*cmd = t;
		sdata->x = -1;
		if (sdata->c == 1)
			sdata->c = -1;
		if (sdata->n == 1)
			sdata->n = -1;
	}
	free(tmp);
	return (1);
}

int	pars_chmp_nm_cm(t_asmdata *data, char *line)
{
	char	*tmp;

	tmp = avoid_comment(ft_strtrim(data->e + line));
	if (data->e > 0 && (data->n == 1 || data->c == 1) && ft_strlen(tmp) != 0)
	{
		free(tmp);
		return (0);
	}
	free(tmp);
	if (data->n == 1 && data->s && data->e && data->x == -1)
	{
		data->name = ft_strscpy(ft_strnew(PROG_NAME_LENGTH), line, data->s, data->e);
		if (data->name)
			data->n = -1;
	}
	if (data->c == 1 && data->s && data->e && data->x == -1)
	{
		data->comment = ft_strscpy(ft_strnew(COMMENT_LENGTH), line, data->s, data->e);
		if (data->comment)
			data->c = -1;
	}
	if (data->s && (data->c == 1 || data->n == 1))
	{
		data->x++;
		if (data->n == 1)
			return (join(line, data, &data->name, PROG_NAME_LENGTH));
		if (data->c == 1)
			return (join (line, data, &data->comment, COMMENT_LENGTH));
	}
	return (1);
}

int	search_for_exention(char *line, t_asmdata *data, int j)
{
	while (line[++j])
		if (line[j] != ' ' && line[j] != '\t')
			break ;
	if (line[j] == '.')
	{
		if (cmp_nm_cm(j + line) > 0)
		{
			if (data->s && !data->e)
				return (-1);
			data->e = 0;
			data->s = 0;
			data->x = -1;
			if ((cmp_nm_cm(j + line) == 1 && data->n == -1)
				|| (cmp_nm_cm(j + line) == 2 && data->c == -1))
				return (-2);
			if (cmp_nm_cm(j + line) == 1)
				data->n = 1;
			if (cmp_nm_cm(j + line) == 2)
				data->c = 1;
			if (data->n == 1)
				j += 4;
			if (data->c == 1)
				j += 7;
			return (j);
		}
	}
	return (-1);
}

int	check_champion (char *line, t_asmdata *sdata)
{
	int	j;

	j = -1;
	j = search_for_exention(line, sdata, j);
	if (sdata->n != 1 && sdata->c != 1)
		return (1);
	while (line[++j])
	{
		if (line[j] != ' ' && line[j] != '\t'
			&& line[j] != '"' && sdata->x == -1 && !sdata->s)
			return (0);
		if (line[j] == '"' && sdata->s && !sdata->e)
			sdata->e = j + 1;
		if (line[j] == '"' && !sdata->s)
			sdata->s = j + 1;
	}
	return (pars_chmp_nm_cm(sdata, line));
}
