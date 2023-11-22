/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:17:12 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/22 18:17:13 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void destroy_image(void *mlx_ptr, void *img_ptr) {
    if (img_ptr != NULL)
        mlx_destroy_image(mlx_ptr, img_ptr);
}

void free_data(t_data *data) {
    if (!data) {
        return;
    }
    if (data->wall_img != NULL)
        destroy_image(data->mlx_ptr, data->wall_img);
    if (data->floor_img != NULL)
        destroy_image(data->mlx_ptr, data->floor_img);
    if (data->player_img != NULL)
        destroy_image(data->mlx_ptr, data->player_img);
    if (data->door_img != NULL)
        destroy_image(data->mlx_ptr, data->door_img);
    if (data->coin_img != NULL)
        destroy_image(data->mlx_ptr, data->coin_img);

    if (data->map != NULL) {
        for (int i = 0; i < data->map_height; ++i)
            free(data->map[i]);
        free(data->map);
    }

    if (data->mlx_ptr != NULL) {
        if(data->win_ptr)
            mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
    }

    free(data);
}
