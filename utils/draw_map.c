/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:17:07 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/23 00:43:47 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	*norm(t_data *data, int x, int y)
{
	if (data->map[y][x] == '0')
		return (data->floor_img);
	if (data->map[y][x] == '1')
		return (data->wall_img);
	if (data->map[y][x] == 'P')
		return (data->player_img);
	if (data->map[y][x] == 'C')
		return (data->coin_img);
	if (data->map[y][x] == 'E')
		return (data->door_img);
	return (NULL);
}

int	draw_map(t_data *data)
{
	void	*img_to_draw;
	int		y;
	int		x;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			img_to_draw = NULL;
			img_to_draw = norm(data, x, y);
			if (data->map[y][x] != '\0' && img_to_draw == NULL)
				return (0);
			if (img_to_draw)
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					img_to_draw, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
	return (1);
}
