#include "../so_long.h"

int get_len(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

int validate_and_count_map(const char *filename, t_data *data) {
    int fd = open(filename, O_RDONLY);
    int line_count = 0;
    int line_width = 0;
    char *line;
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }
    while ((line = get_next_line(fd)) != NULL) {
        int len = get_len(line);
        if (line[len - 1] == '\n')
            len-= 1;
		len++;
        if (line_count == 0) {
            line_width = len;
            data->map_width = line_width;
        }
        if (len != line_width) {
            perror("Map is not a rectangle");
            free(line);
            close(fd);
            return -1;
        }

        free(line);
        line_count++;
    }
    close(fd);
    if (line_count > 0)
        data->map_height = line_count;
    else {
        perror("No data in file or error reading file");
        return -1;
    }
    return 0;
}
