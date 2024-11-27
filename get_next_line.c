/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:19:10 by mbousset          #+#    #+#             */
/*   Updated: 2024/11/27 14:11:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_fails(int fd, char *buf, char **rest)
{
	if (read(fd, 0, 0) == -1)
	{
		free(buf);
		if (*rest != NULL)
			free(*rest);
		*rest = NULL;
		return (1);
	}
	return (0);
}

char	*checkline_in_rest(char **rest)
{
	int	i;

	i = 0;
	if (*rest)
	{
		while ((*rest)[i] && (*rest)[i] != '\n')
			i++;
		if ((*rest)[i] == '\n')
			return (jbad_line(rest, i, 1));
	}
	return (NULL);
}

char	*proccess_buffer(int fd, char *buf, char **res)
{
	char	*temp;
	int		n;
	int		i;

	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n <= 0)
			break ;
		buf[n] = '\0';
		temp = *res;
		*res = ft_strjoin(*res, buf);
		free(temp);
		if (!*res)
			return (*res = NULL, NULL);
		i = 0;
		while ((*res)[i] && (*res)[i] != '\n')
			i++;
		if ((*res)[i] == '\n')
			return (jbad_line(res, i, 1));
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(rest), rest = NULL, NULL);
	line = checkline_in_rest(&rest);
	if (line)
		return (free(buf), line);
	if (read_fails(fd, buf, &rest))
		return (NULL);
	line = proccess_buffer(fd, buf, &rest);
	if (line)
		return (free(buf), line);
	if (line == NULL && (!rest || *rest == '\0'))
		return (free(buf), free(rest), rest = NULL, NULL);
	line = jbad_line(&rest, ft_strlen(rest), 0);
	free(buf);
	return (line);
}
