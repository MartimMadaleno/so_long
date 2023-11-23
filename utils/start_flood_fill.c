/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_flood_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:17:23 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/23 20:45:44 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int	find_plr(t_data *data, int x, int y, int *start)
{
	if (data->map[y][x] == 'P')
	{
		if (start[0] != -1)
			return (0);
		start[1] = x;
		start[0] = y;
	}
	if (data->map[y][x] == 'E')
	{
		data->coins++;
		if (data->coins != 1)
			return (0);
	}
	return (1);
}

int	fill_visited(t_data *data, int *start, char **visited)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < data->map_height)
	{
		visited[y] = ft_calloc(sizeof(char), data->map_width);
		while (x < data->map_width)
		{
			if (!find_plr(data, x, y, start))
				return (0);
			x++;
		}
		x = 0;
		y++;
	}
	data->coins = 0;
	return (1);
}

static char	**malloc_and_init_visited(t_data *data)
{
	char	**visited;

	visited = ft_calloc(sizeof(char *), data->map_height);
	if (!visited)
		return (NULL);
	return (visited);
}

static int	flood_fill(t_data *data, int x, int y, char **visited)
{
	if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height
		|| visited[y][x] || data->map[y][x] == '1')
		return (0);
	visited[y][x] = 1;
	if (data->map[y][x] == 'C')
		data->coins++;
	if (data->map[y][x] == 'E')
		data->exit_found = 1;
	flood_fill(data, x + 1, y, visited);
	flood_fill(data, x - 1, y, visited);
	flood_fill(data, x, y + 1, visited);
	flood_fill(data, x, y - 1, visited);
	return (data->exit_found);
}

int	start_flood_fill(t_data *data, int result)
{
	int		start[2];
	char	**visited;

	start[0] = -1;
	start[1] = -1;
	result = 0;
	visited = malloc_and_init_visited(data);
	if (!visited)
		return (0);
	if (!fill_visited(data, start, visited) || (start[1] == -1 || start[0] 
			== -1))
	{
		free_map(visited, data->map_height);
		return (0);
	}
	result = flood_fill(data, start[1], start[0], visited);
	free_map(visited, data->map_height);
	if (data->maxcoins <= 0)
		return (0);
	if (data->coins != data->maxcoins)
		return (0);
	data->coins = 0;
	return (result);
}
