/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsantand <nsantand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 12:47:59 by nsantand          #+#    #+#             */
/*   Updated: 2024/11/30 12:47:59 by nsantand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line_buff(char *line, char **remain)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
	{
		if (*remain)
			free(*remain);
		return (*remain = NULL, line);
	}
	if (*remain)
		free(*remain);
	*remain = ft_substr(line, i + 1, len - i);
	if (!*remain)
		return (free(line), NULL);
	line[i + 1] = '\0';
	return (line);
}

char	*read_lines(int fd, char *line, char **remain)
{
	ssize_t	read_bytes;
	char	*buff;
	char	*temp;

	line = ft_strjoin(line, *remain);
	if (*remain)
		free(*remain);
	*remain = NULL;
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (free(line), NULL);
	read_bytes = 1;
	while (!ft_strchr(line, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (free(buff), free(line), NULL);
		buff[read_bytes] = '\0';
		temp = line;
		line = ft_strjoin(line, buff);
		free(temp);
		if (!line)
			break ;
	}
	return (free(buff), line);
}

char	*get_next_line(int fd)
{
	static char	*remain[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	line = read_lines(fd, line, &remain[fd]);
	line = get_line_buff(line, &remain[fd]);
	if (!line || *line == '\0')
		return (free(line), NULL);
	return (line);
}

// int	main(void)
// {
// 	int fd1;
// 	int fd2;
// 	char *line;

// 	fd1 = open("multiple_nl.txt", O_RDONLY);
// 	fd2 = open("digue.txt", O_RDONLY);
// 	line = get_next_line(fd1);
// 	printf("El resultado de la lectura es: %s", line);
// 	free(line);
// 	line = get_next_line(fd2);
// 	printf("El resultado de la lectura es: %s", line);
// 	free(line);
// 	line = get_next_line(fd1);
// 	printf("El resultado de la lectura es: %s", line);
// 	free(line);
// 	return (0);
// }