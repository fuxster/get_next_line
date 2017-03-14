/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrumus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/07 19:13:19 by hdrumus           #+#    #+#             */
/*   Updated: 2017/03/09 19:31:03 by hdrumus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	init(char **data, char *buff)
{
	char *temp;

	if (!*data)
	{
		*data = (char *)malloc(sizeof(char) * ft_strlen(buff));
		ft_bzero(*data, ft_strlen(*data));
	}
	if (buff)
	{
		temp = ft_strjoin(*data, buff);
		free(*data);
		*data = NULL;
		*data = ft_strdup(temp);
		free(temp);
		temp = NULL;
	}
}

char	*get_one(char *buff)
{
	static char	*data;
	char		*line;
	char		*eol;

	init(&data, buff);
	if ((eol = ft_strchr(data, '\n')) != 0)
	{
		*eol = '\0';
		line = ft_strdup(data);
		free(data);
		data = NULL;
		init(&data, eol + 1);
		return (line);
	}
	if (buff[0] == '\0')
	{
		if (!(eol = ft_strchr(data, '\n')) && (ft_strlen(data) != 0))
		{
			line = ft_strdup(data);
			free(data);
			data = NULL;
			return (line);
		}
	}
	return (NULL);
}

int		get_next_line(int fd, char **line)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;

	if (fd < 0 || BUFF_SIZE == 0 || !line)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if ((*line = get_one(buff)))
			return (1);
	}
	if (ret == -1)
		return (-1);
	if ((*line = get_one("\0")) != NULL)
		return (1);
	return (0);
}
