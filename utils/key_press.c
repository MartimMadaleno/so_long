/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 01:07:25 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/23 20:53:58 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	update_player_position(int keycode, t_data *data, int player[2])
{
	if ((keycode == 65362 || keycode == 119) && player[1] > 0
		&& data->map[player[1] - 1][player[0]] != '1')
		player[1]--;
	else if ((keycode == 65364 || keycode == 115)
		&& player[1] < data->map_height - 1 && data->map[player[1]
			+ 1][player[0]] != '1')
		player[1]++;
	else if ((keycode == 65363 || keycode == 100) && player[0] < data->map_width
		- 1 && data->map[player[1]][player[0] + 1] != '1')
		player[0]++;
	else if ((keycode == 65361 || keycode == 97) && player[0] > 0
		&& data->map[player[1]][player[0] - 1] != '1')
		player[0]--;
}

int	handle_coin_and_exit(t_data *data, int player[2])
{
	if (data->map[player[1]][player[0]] == 'C')
		data->coins++;
	if (data->map[player[1]][player[0]] == 'E')
	{
		if (data->coins == data->maxcoins)
		{
			ft_putstr("You Win!\n");
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
	return (1);
}

void	move_player(t_data *data, int old[2], int player[2])
{
	if (player[0] == old[0] && player[1] == old[1])
		return ;
	data->steps++;
	ft_putstr("Steps: ");
	ft_putnbr(data->steps);
	putchar('\n');
	data->map[old[1]][old[0]] = '0';
	data->map[player[1]][player[0]] = 'P';
}

void	find_player_position(t_data *data, int player[2])
{
	int	y;
	int	x;

	player[0] = -1;
	player[1] = -1;
	y = 0;
	while (y < data->map_height && (player[1] == -1 || player[0] == -1))
	{
		x = 0;
		while (x < data->map_width && (player[1] == -1 || player[0] == -1))
		{
			if (data->map[y][x] == 'P')
			{
				player[0] = x;
				player[1] = y;
			}
			x++;
		}
		y++;
	}
}

int	key_press(int keycode, t_data *data)
{
	int	player[2];
	int	old[2];

	if (keycode == 65307)
	{
		free_data(data);
		exit(0);
	}
	find_player_position(data, player);
	old[0] = player[0];
	old[1] = player[1];
	update_player_position(keycode, data, player);
	if (!handle_coin_and_exit(data, player))
		return (0);
	move_player(data, old, player);
	draw_map(data);
	mlx_do_sync(data->mlx_ptr);
	return (0);
}
