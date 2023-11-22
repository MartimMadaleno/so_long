/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:16:43 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/22 18:16:54 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
	#include "./mlx/mlx.h"
	#include <fcntl.h>
	#include <unistd.h>
	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>
	#include "get_next_line/get_next_line.h"

	typedef struct s_data {
		void *mlx_ptr;
		void *win_ptr;
		void *wall_img;
		void *floor_img;
		void *player_img;
		void *door_img;
		void *coin_img;
		char **map;
		int map_width;
    	int map_height;
		int coins;
		int maxcoins;
		int steps;
		int exit_found;
	} t_data;

	#define MAX_LINE_LENGTH 1024
	#define TILE_SIZE 100
	#define MAP_WIDTH 10
	#define MAP_HEIGHT 10
	int draw_map(t_data *data);
	int read_map(const char *filename, t_data *data);
	int key_press(int keycode, t_data *data );
	int is_map_closed(t_data *data);
	int validate_and_count_map(const char *filename, t_data *data);
	int start_flood_fill(t_data *data);
	void free_data(t_data *data);
#endif