/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 03:23:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/13 03:23:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_server.h"

void	init_map_data(t_map *map)
{
	ft_bzero(map->path, sizeof (char *) * 7);
	map->spawn = NULL;
	map->map = NULL;
}

/**
 * @brief Check if the file extension is .cub
 */
int	is_valid_filename(char *filename)
{
	const size_t	len = ft_strlen(filename);

	return (ft_strcmp(filename + (len - 4), ".cub") == 0);
}

void	map_data_clear(t_map *map)
{
	free(map->path[NORTH_ID]);
	free(map->path[SOUTH_ID]);
	free(map->path[EAST_ID]);
	free(map->path[WEST_ID]);
	free(map->path[FLOOR_ID]);
	free(map->path[CEILING_ID]);
	free(map->path[DOOR_ID]);
	ft_lstclear(&map->spawn, free);
	if (map->map)
		free_string_array(map->map);
}
