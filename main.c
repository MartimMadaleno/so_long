/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:15:02 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/23 20:20:02 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_window_close(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	init_data(t_data *data)
{
	data->coins = 0;
	data->maxcoins = 0;
	data->steps = 0;
	data->map_height = 0;
	data->map_width = 0;
}

static void	set_img(t_data *data)
{
	data->wall_img = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/wall.xpm",
			&(int){TILE_SIZE}, &(int){TILE_SIZE});
	data->floor_img = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/floor.xpm",
			&(int){TILE_SIZE}, &(int){TILE_SIZE});
	data->player_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assets/player.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	data->coin_img = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/coin.xpm",
			&(int){TILE_SIZE}, &(int){TILE_SIZE});
	data->door_img = mlx_xpm_file_to_image(data->mlx_ptr,
			"./assets/doorfloor.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	if (!data->wall_img || !data->floor_img || !data->player_img
		|| !data->coin_img || !data->door_img)
		h_error(data, "Error img\n");
}

static void	norm_h(t_data *data, char **argv)
{
	if (!validate_and_count_map(argv[1], data))
		h_error(data, "Failed to determine the map size.\n");
	if (data->map_height == data->map_width - 1)
		h_error(data, "Map needs to be rectangular!\n");
	data->map = malloc(sizeof(char *) * data->map_height);
	if (!data->map)
		h_error(data, "Failed to allocate memory for the map.\n");
	if (!read_map(argv[1], data))
		h_error(data, "Failed to read the map from the file.\n");
	data->map_width--;
	if (!is_map_closed(data))
		h_error(data, "Map needs to be surrounded by borders(1)\n");
	if (!start_flood_fill(data, 0))
		h_error(data, "Map is not valid: (Impossible to complete)\n");
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		e_error("Usage: ./so_long <map.ber>\n");
	data = ft_calloc(sizeof(t_data), 1);
	norm_h(data, argv);
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		h_error(data, "Error mlx_ptr!\n");
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width * TILE_SIZE,
			data->map_height * TILE_SIZE, "So Long");
	if (!data->win_ptr)
		h_error(data, "Error win_ptr!\n");
	set_img(data);
	if (!draw_map(data))
		h_error(data, "Invalid map!\n");
	mlx_hook(data->win_ptr, 2, 1L << 0, key_press, data);
	mlx_hook(data->win_ptr, 17, 1L << 17, handle_window_close, data);
	mlx_loop(data->mlx_ptr);
	free_data(data);
	return (0);
}
