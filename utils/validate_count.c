/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:17:26 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/23 12:54:11 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	get_len(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	gtnl(int fd, int line_count, int *line_width, t_data *data)
{
	int		len;
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		len = get_len(line);
		if (line[len - 1] == '\n')
			len -= 1;
		len++;
		if (line_count == 0)
			*line_width = len;
		if (len != *line_width)
		{
			free(line);
			return (0);
		}
		free(line);
		line_count++;
		line = get_next_line(fd);
	}
	data->map_height = line_count;
	if (line_count <= 0)
		return (0);
	return (1);
}

int	validate_and_count_map(const char *filename, t_data *data)
{
	int		fd;
	int		line_width;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	line_width = 0;
	if (!gtnl(fd, 0, &line_width, data))
	{
		close(fd);
		return (0);
	}
	close(fd);
	data->map_width = line_width;
	return (1);
}
