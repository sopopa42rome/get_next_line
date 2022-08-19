/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sopopa <sopopa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 19:08:58 by sopopa            #+#    #+#             */
/*   Updated: 2022/08/18 18:45:24 by sopopa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_and_save(int fd, char *res)
{
	char	*buffer;
	int		num_bytes;

	if (!res)
		res = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	num_bytes = 1;
	while (num_bytes > 0)
	{
		num_bytes = read(fd, buffer, BUFFER_SIZE);
		if (num_bytes == -1)
		{
			free(buffer);
			return (0);
		}
		buffer[num_bytes] = '\0';
		res = ft_strjoin(res, buffer);
	}
	free(buffer);
	return (res);
}

char	*get_first_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	line = calloc(ft_strlen(save) + 1, sizeof(char));
	while (save[i] != '\n' && save[i] != 0)
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = save[i];
		i++;
	}
	line[i] = '\0';
	free(save);
	return (line);
}

char	*get_the_next(char *save, char *line)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = calloc(ft_strlen(save) - ft_strlen(line), sizeof(char));
	i = ft_strlen(line);
	j = 0;
	while (save[i] != '\0')
	{
		new_line[j] = save[i];
		i++;
		j++;
		if (new_line[j] == '\n')
		{
			new_line[j] = save[i];
			j++;
		}
	}
	new_line[j] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*save[257];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	save[fd] = read_and_save(fd, save[fd]);
	if (!save[fd])
		return (NULL);
	line = get_first_line(save[fd]);
	save[fd] = get_the_next(save[fd], line);
	return (line);
}