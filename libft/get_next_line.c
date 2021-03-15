/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zael-mab <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 20:06:13 by zael-mab          #+#    #+#             */
/*   Updated: 2021/03/15 15:26:00 by zael-mab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_checkfd(char *str, char **line)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	*line = ft_strsub(str, 0, i);
	if (str[i] == '\n')
		temp = ft_strdup(&str[i] + 1);
	if (str[i] == '\0')
		temp = ft_strnew(0);
	return (temp);
}

int			get_next_line(int fd, char **line)
{
	static char		*str[CON_ST];
	char			*temp;
	char			buff[BUFF_SIZE + 1];
	int				rest;

	if (fd < 0 || !line || fd > CON_ST || BUFF_SIZE < 1)
		return (-1);
	if (!str[fd])
		str[fd] = ft_strnew(0);
	while (!ft_strchr(str[fd], '\n') && (rest = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[rest] = '\0';
		temp = ft_strjoin(str[fd], buff);
		free(str[fd]);
		str[fd] = temp;
	}
	if (rest < 0)
		return (-1);
	if (rest == 0 && !ft_strlen(str[fd]))
		return (0);
	temp = ft_checkfd(str[fd], line);
	free(str[fd]);
	str[fd] = temp;
	return (1);
}
