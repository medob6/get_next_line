/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 08:41:25 by mbousset          #+#    #+#             */
/*   Updated: 2024/11/26 15:45:45 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*handel_rest(int fd, char *buf, char **rest)
{
	int	i;

	i = 0;
	if (!rest[fd])
		return (NULL);
	while (rest[fd][i] && rest[fd][i] != '\n')
		i++;
	if (rest[fd][i] == '\n')
		return (free(buf), jbad_line(&rest[fd], i, 1));
	return (NULL);
}

char	*handel_buf(int fd, char *buf, char **rest)
{
	int		i;
	ssize_t	n;
	char	*temp;

	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		buf[n] = '\0';
		temp = rest[fd];
		rest[fd] = ft_strjoin(rest[fd], buf);
		free(temp);
		if (!rest[fd])
			return (free(buf), NULL);
		i = 0;
		while (rest[fd][i] && rest[fd][i] != '\n')
			i++;
		if (rest[fd][i] == '\n')
			return (free(buf), jbad_line(&rest[fd], i, 1));
	}
	if (n < 0)
		return (free(buf), free(rest[fd]), rest[fd] = NULL, NULL);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest[1024];
	char		*buf;
	char		*result;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
	{
		if (rest[fd])
			return (free(rest[fd]), rest[fd] = NULL, NULL);
		return (rest[fd] = NULL, NULL);
	}
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(rest[fd]), rest[fd] = NULL, NULL);
	line = handel_rest(fd, buf, rest);
	if (line)
		return (line);
	result = handel_buf(fd, buf, rest);
	if (result)
		return (result);
	if (!rest[fd] || !*rest[fd])
		return (free(buf), free(rest[fd]), rest[fd] = NULL, NULL);
	result = jbad_line(&rest[fd], ft_strlen(rest[fd]), 0);
	return (free(buf), result);
}
