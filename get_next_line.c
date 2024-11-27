/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:19:10 by mbousset          #+#    #+#             */
/*   Updated: 2024/11/27 12:05:03 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "get_next_line.h"

// char	*process_rest(char **rest, char *buf)
// {
// 	int	i;

// 	i = 0;
// 	if (!*rest)
// 		return (NULL);
// 	while ((*rest)[i] && (*rest)[i] != '\n')
// 		i++;
// 	if ((*rest)[i] == '\n')
// 		return (free(buf), jbad_line(rest, i, 1));
// 	return (NULL);
// }

// char	*read_and_process(int fd, char **rest, char *buf)
// {
// 	ssize_t	n;
// 	char	*temp;
// 	char	*line;

// 	line = process_rest(rest, buf);
// 	if (line)
// 		return (line);
// 	n = 1;
// 	while (n > 0)
// 	{
// 		n = read(fd, buf, BUFFER_SIZE);
// 		buf[n] = '\0';
// 		temp = *rest;
// 		*rest = ft_strjoin(*rest, buf);
// 		free(temp);
// 		if (!*rest)
// 			return (free(buf), NULL);
// 		line = process_rest(rest, buf);
// 		if (line)
// 			return (line);
// 	}
// 	if (n <= 0)
// 		return (free(buf), free(*rest), *rest = NULL, NULL);
// 	return (NULL);
// }

// char	*get_next_line(int fd)
// {
// 	static char	*rest;
// 	char		*buf;
// 	char		*result;

// 	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
// 	{
// 		if (rest)
// 			return (free(rest), rest = NULL, NULL);
// 		else
// 			return (NULL);
// 	}
// 	buf = malloc(BUFFER_SIZE + 1);
// 	if (!buf)
// 		return (free(rest), rest = NULL, NULL);
// 	result = read_and_process(fd, &rest, buf);
// 	if (!result || (!result && (!rest || *rest == '\0')))
// 	{
// 		if (rest)
// 			return (free(rest), rest = NULL, NULL);
// 		else
// 			return (NULL);
// 	}
// 	if (result)
// 		return (result);
// 	result = jbad_line(&rest, ft_strlen(rest), 0);
// 	return (result);
// }
#include "get_next_line.h"

// char *handel_rest()
// {

// }
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

char	*checkline_in_rest(char **rest, char *buf)
{
	int	i;

	i = 0;
	(void )buf;
	if (*rest)
	{
		while ((*rest)[i] && (*rest)[i] != '\n')
			i++;
		if ((*rest)[i] == '\n')
			return (jbad_line(rest, i, 1));
	}
	return (NULL);
}

char *proccess_buffer(int fd,char *buf,char **res)
{	
	char		*temp;
	int i;
	int n;
	
	n = 1;
	while (n > 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		buf[n] = '\0';
		temp = *res;
		*res = ft_strjoin(*res, buf);
		free(temp);
		if (!*res)
			return (free(buf), free(*res), *res = NULL, NULL);
		i = 0;
		while (*res[i] && *res[i] != '\n')
			i++;
		if (*res[i] == '\n')
			return (free(buf), jbad_line(res, i, 1));
	}
	return (NULL);
}
char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buf;
	char		*result;
	int			i;
	int			n = 0;
	

	i = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(rest), rest = NULL, NULL);
	char *line = checkline_in_rest(&rest,buf);
	if (line)
		return (free(buf),line);
	if (read_fails(fd, buf, &rest))
		return (NULL);
	line = proccess_buffer(fd,buf,&rest);
	if (line)
		return (n = 1,line);
	if (n == -1 || (n == 0 && (!rest || *rest == '\0')))
		return (free(buf), free(rest), rest = NULL, NULL);
	result = jbad_line(&rest, ft_strlen(rest), 0);
	return (free(buf), result);
}
