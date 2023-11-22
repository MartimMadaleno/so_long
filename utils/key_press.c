#include "../so_long.h"

int key_press(int keycode, t_data *data)
{
    if (keycode == 65307)
    {
        free_data(data);
        exit(0);
    }

    int player_x = -1;
    int player_y = -1;
    for (int y = 0; y < data->map_height; y++)
        for (int x = 0; x < data->map_width; x++)
            if (data->map[y][x] == 'P')
            {
                player_x = x;
                player_y = y;
            }
    int old_x = player_x;
    int old_y = player_y;

    if (keycode == 65362 || keycode == 119)
        player_y -= (player_y > 0 && data->map[player_y - 1][player_x] != '1') ? 1 : 0;
    else if (keycode == 65364 || keycode == 115)
        player_y += (player_y < data->map_height - 1 && data->map[player_y + 1][player_x] != '1') ? 1 : 0;
    else if (keycode == 65363 || keycode == 100)
        player_x += (player_x < data->map_width - 1 && data->map[player_y][player_x + 1] != '1') ? 1 : 0;
    else if (keycode == 65361 || keycode == 97)
        player_x -= (player_x > 0 && data->map[player_y][player_x - 1] != '1') ? 1 : 0;
    if (player_x >= 0 && player_y >= 0)
    {
		if(data->map[player_y][player_x] == 'C')
			data->coins++;
		if(data->map[player_y][player_x] == 'E')
		{
			if(data->coins == data->maxcoins)
			{
				printf("Win!!!\n");
				free_data(data);
        		exit(0);
			}
			else
			{
				draw_map(data);
   				mlx_do_sync(data->mlx_ptr);
    			return (0);
			}
		}
        if((player_x == old_x) && (player_y == old_y))
            return(0);
		data->steps++;
		printf("%i\n", data->steps);
        data->map[old_y][old_x] = '0';
        data->map[player_y][player_x] = 'P';
    }
    draw_map(data);
    mlx_do_sync(data->mlx_ptr);
    return (0);
}