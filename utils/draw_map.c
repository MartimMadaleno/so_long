#include "../so_long.h"

int draw_map(t_data *data) {
    for (int y = 0; y < data->map_height; y++) {
        for (int x = 0; x < data->map_width; x++) {
            void *img_to_draw = NULL; 
			if (data->map[y][x] == '0') {
                img_to_draw = data->floor_img;
            } else if (data->map[y][x] == '1') {
                img_to_draw = data->wall_img;
            } else if (data->map[y][x] == 'P') {
                
				img_to_draw = data->player_img;
            } else if (data->map[y][x] == 'C') {
				img_to_draw = data->coin_img;
            } else if (data->map[y][x] == 'E') {
				img_to_draw = data->door_img;
            } else if(data->map[y][x] != '\0')
				return 0;
			if(img_to_draw)
            	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img_to_draw, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
	return 1;
}