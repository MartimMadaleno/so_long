/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmendes- <mmendes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 18:17:38 by mmendes-          #+#    #+#             */
/*   Updated: 2023/11/23 00:25:02 by mmendes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

int	ft_limpamemo(char *buff)
{
	int	i;
	int	is_nline;
	int	j;

	i = 0;
	j = 0;
	is_nline = 0;
	while (buff[i])
	{
		if (is_nline)
			buff[j++] = buff[i];
		if (buff[i] == '\n')
			is_nline = 1;
		buff[i++] = '\0';
	}
	return (is_nline);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!newstr)
		return (NULL);
	while (str1 && str1[i])
	{
		newstr[i] = str1[i];
		i++;
	}
	free(str1);
	while (*str2)
	{
		newstr[i++] = *str2;
		if (*str2++ == '\n')
			break ;
	}
	newstr[i] = '\0';
	return (newstr);
}
