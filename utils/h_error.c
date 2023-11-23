/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 17:32:12 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/23 18:03:20 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	h_error(t_data *data, char *str)
{
	free_data(data);
	perror(str);
	exit(EXIT_FAILURE);
}

void	e_error(char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
