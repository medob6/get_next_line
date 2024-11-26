/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:19:10 by mbousset          #+#    #+#             */
/*   Updated: 2024/11/26 15:23:55 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*process_rest(char **rest, char *buf)
{
	int	i;

	i = 0;
	if (!*rest)
		return (NULL);
	while ((*rest)[i] && (*rest)[i] != '\n')
		i++;
	if ((*rest)[i] == '\n')
		return (free(buf), jbad_line(rest, i, 1));
	return (NULL);
}

char	*read_and_process(int fd, char **rest, char *buf)
{
	ssize_t	n;
	char	*temp;
	char	*line;

	line = process_rest(rest, buf);
	if (line)
		return (line);
	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		buf[n] = '\0';
		temp = *rest;
		*rest = ft_strjoin(*rest, buf);
		free(temp);
		if (!*rest)
			return (free(buf), NULL);
		line = process_rest(rest, buf);
		if (line)
			return (line);
	}
	if (n < 0)
		return (free(buf), free(*rest), *rest = NULL, NULL);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest = NULL;
	char		*buf;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
	{
		if (rest)
			return (free(rest), rest = NULL, NULL);
		else
			return (NULL);
	}
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(rest), rest = NULL, NULL);
	result = read_and_process(fd, &rest, buf);
	if (result)
		return (result);
	if (rest && *rest)
	{
		result = jbad_line(&rest, ft_strlen(rest), 0);
		return (free(buf), result);
	}
	return (free(buf), free(rest), rest = NULL, NULL);
}
