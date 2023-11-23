/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:17:21 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/23 01:12:03 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	cpy_str(char *dest, char *src, int n, t_data *data)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (src[i] == 'C')
			data->maxcoins++;
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	read_map(const char *filename, t_data *data)
{
	int		fd;
	char	*line;
	int		current_line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	current_line = 0;
	while (line != NULL)
	{
		if (current_line >= data->map_height)
		{
			free(line);
			close(fd);
			return (0);
		}
		data->map[current_line] = malloc(sizeof(char) * data->map_width);
		cpy_str(data->map[current_line], line, data->map_width - 1, data);
		free(line);
		current_line++;
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
