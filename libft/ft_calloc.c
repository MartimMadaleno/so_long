/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 19:21:45 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/23 18:16:05 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*p;

	p = malloc(nitems * size);
	if (!p)
		return (NULL);
	ft_bzero(p, nitems * size);
	return (p);
}
