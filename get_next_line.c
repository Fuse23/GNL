/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: falarm <falarm@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 18:05:35 by falarm            #+#    #+#             */
/*   Updated: 2021/10/26 20:05:19 by falarm           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*check_remainder(char **remainder, char **line)
{
	char	*p;
	char	*tmp;

	p = NULL;
	if (*remainder)
	{
		p = ft_strchr(*remainder, '\n');
		if (p)
		{
			*p = '\0';
			*line = ft_strdup(*remainder);
			tmp = *remainder;
			*remainder = ft_strdup(++p);
			free(tmp);
		}
		else
		{
			*line = ft_strdup(*remainder);
			free(*remainder);
			*remainder = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (p);
}

void	write_remainder(char **remainder, char **p)
{
	if (*p)
	{
		**p = '\0';
		if (*remainder)
		{
			free(*remainder);
			*remainder = NULL;
		}
		*remainder = ft_strdup(++(*p));
	}
}

void	write_line(char **line, const char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
}

void	last(int bwr, char **line, char *remaider)
{
	if (bwr || ft_strlen(remaider))
		write_line(line, "\n");
	if (!(bwr || ft_strlen(remaider) || ft_strlen(*line)))
	{
		free(*line);
		*line = NULL;
	}
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buf[BUFFER_SIZE + 1];
	char		*line;
	char		*p;
	int			byte_was_read;

	if (read(fd, 0, 0) < 0)
		return (NULL);
	p = check_remainder(&remainder, &line);
	byte_was_read = 1;
	while (!p && byte_was_read)
	{
		if (!p)
			byte_was_read = read(fd, buf, BUFFER_SIZE);
		buf[byte_was_read] = '\0';
		p = ft_strchr(buf, '\n');
		write_remainder(&remainder, &p);
		write_line(&line, buf);
	}
	last(byte_was_read, &line, remainder);
	return (line);
}
