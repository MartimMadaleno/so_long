#include "../so_long.h"

void cpy_str(char *dest, char *src, int n, t_data *data)
{
	int i = 0;
	while(i < n)
	{
		if(src[i] == 'C')
			data->maxcoins++;
		dest[i] = src[i];
		i++;
	}
    dest[i] = '\0';
}

int read_map(const char *filename, t_data *data) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 0;
    }

    char *line = NULL;
    int current_line = 0;

    while ((line = get_next_line(fd)) != NULL) {
        if (current_line >= data->map_height) {
            perror("File has more lines than expected");
            free(line);
            close(fd);
            return 0;
        }
		data->map[current_line] = malloc(sizeof(char) * data->map_width);
		cpy_str(data->map[current_line], line, data->map_width - 1, data);
        free(line);
        current_line++;
    }
    close(fd);
    return 1;
}