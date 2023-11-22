/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:15:02 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/22 18:15:03 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int handle_window_close(t_data *data)
{
	free_data(data);
	exit(EXIT_SUCCESS);
}

void print_map(char **map, int line_count, int line_len) {
    for (int i = 0; i < line_count; i++) {
		int h = 0;
		while (h < line_len)
		{
        	printf("'%c' ", map[i][h]);
			h++;
		}
		printf("\n");
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <map.ber>\n", argv[0]);
        return EXIT_FAILURE;
    }

	t_data *data;
	data = calloc(sizeof(t_data), 1);
	data->coins = 0;
	data->maxcoins = 0;
	data->steps = 0;
	data->map_height = 0;
	data->map_width = 0;
	validate_and_count_map(argv[1], data);
    if (data->map_height <= 0) {
		free_data(data);
        fprintf(stderr, "Failed to determine the map size.\n");
        return EXIT_FAILURE;
    }
    data->map = malloc(sizeof(char*) * data->map_height);
    if (!data->map) {
		free_data(data);
        fprintf(stderr, "Failed to allocate memory for the map.\n");
        return EXIT_FAILURE;
    }
    if (!read_map(argv[1], data)) {
		free_data(data);
        fprintf(stderr, "Failed to read the map from the file.\n");
        return EXIT_FAILURE;
    }
	data->map_width--;
	if(!is_map_closed(data))
	{
		free_data(data);
		perror("Map needs to be surrounded by borders(1)");
		return 1;
	}
	if(!start_flood_fill(data))
	{
		free_data(data);
		perror("Map is not valid: (Impossible to complete)");
		return 1;
	}
	data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
	{
		free_data(data);
		perror("Error mlx_ptr!");
        return (1);
	}
    data->win_ptr = mlx_new_window(data->mlx_ptr, data->map_width * TILE_SIZE, data->map_height * TILE_SIZE, "So Long");
    if (!data->win_ptr)
	{
		free_data(data);
		perror("Error win_ptr!");
        return (1);
	}
    data->wall_img = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/wall.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    data->floor_img = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/floor.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
    data->player_img = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/player.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	data->coin_img = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/coin.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	data->door_img = mlx_xpm_file_to_image(data->mlx_ptr, "./assets/doorfloor.xpm", &(int){TILE_SIZE}, &(int){TILE_SIZE});
	if (!data->wall_img || !data->floor_img || !data->player_img  || !data->coin_img  || !data->door_img) {
		free_data(data);
		perror("Error img");
		return 1;
	}
	if (!draw_map(data))
	{
		free_data(data);
		perror("Invalid map!");
		return 1;
	}
	print_map(data->map, data->map_height, data->map_width);
	mlx_hook(data->win_ptr, 2, 1L<<0, key_press, data);
	mlx_hook(data->win_ptr, 17, 1L<<17, handle_window_close, data);
	mlx_loop(data->mlx_ptr);
	free_data(data);
	return 0;
}