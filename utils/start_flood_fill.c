#include "../so_long.h"

void free_map(char** map, int map_height) {
	int i;
	i = 0;
	while(i < map_height){
        free(map[i]);
		i++;
	}
    free(map);
}

int flood_fill(t_data *data, int x, int y, char **visited) {
    if (x < 0 || x >= data->map_width || y < 0 || y >= data->map_height || 
        visited[y][x] || data->map[y][x] == '1') {
        return 0;
    }
    visited[y][x] = 1;
    if (data->map[y][x] == 'C')
        data->coins++;
    if (data->map[y][x] == 'E')
        data->exit_found = 1;
    flood_fill(data, x + 1, y, visited);
    flood_fill(data, x - 1, y, visited);
    flood_fill(data, x, y + 1, visited);
    flood_fill(data, x, y - 1, visited);
    return data->exit_found;
}

int start_flood_fill(t_data *data) {
    int x = 0;
    int y = 0;
    int i = 0;
    char **visited;
    int hasE = 0;
    int start_x = -1;
    int start_y = -1;
    int result = 0;

    visited = malloc(sizeof(char *) * data->map_height);
    while(x < data->map_height)
    {
        visited[x] = malloc(data->map_width * sizeof(char));
        while( i < data->map_width)
        {
            visited[x][i] = '\0';
            i++;
        }
        i = 0;
        x++;
    }
    x = 0;
    while(y < data->map_height)
    {
        while(x < data->map_width)
        {
            if (data->map[y][x] == 'P') {
                if(start_x != -1)
                {
                    free_map(visited, data->map_height);
                    return(0);
                }
                start_x = x;
                start_y = y;
            }
            if (data->map[y][x] == 'E') {
                hasE++;
                if(hasE != 1)
                {
                    free_map(visited, data->map_height);
                    return(0);
                }
            }
            x++;
        }
        x = 0;
        y++;
    }
    if (start_x != -1 && start_y != -1) {
        result = flood_fill(data, start_x, start_y, visited);
    }
	else
	{
		free_map(visited, data->map_height);
		return 0;
	}
    free_map(visited, data->map_height);
    if (data->maxcoins <= 0)
        return 0;
    if (data->coins != data->maxcoins)
        return 0;
    data->coins = 0;
    return result;
}