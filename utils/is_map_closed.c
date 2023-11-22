/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_closed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:17:16 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/22 18:17:17 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

int is_map_closed(t_data *data) {
    int i;
    
    i = 0;
    while (i < data->map_width){
        if (data->map[0][i] != '1' || data->map[data->map_height - 1][i] != '1') {
            return 0;
        }
        i++;
    }
    i = 0;
    while (i < data->map_height) {
        if (data->map[i][0] != '1' || data->map[i][data->map_width - 1] != '1') {
            return 0;
        }
        i++;
    }

    return 1;
}