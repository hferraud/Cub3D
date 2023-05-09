/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 02:01:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/04/04 02:01:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_client.h"

void	map_clear(t_map_client *map)
{
	int	index;

	index = 0;
	while (index < 7)
	{
		free(map->path[index]);
		index++;
	}
	free_string_array(map->map);
	if (map->collectible_data.collectible_lock)
	{
		pthread_mutex_destroy(map->collectible_data.collectible_lock);
		free(map->collectible_data.collectible_lock);
	}
}
