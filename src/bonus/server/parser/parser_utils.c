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
#include "parser_bonus.h"

void	init_map_data(t_map *map)
{
	ft_bzero(map->wall_path, sizeof (char *) * 4);
	ft_bzero(map->horizontal_plane_path, sizeof (char *) * 2);
	map->door_path = NULL;
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
	free(map->wall_path[NORTH]);
	free(map->wall_path[SOUTH]);
	free(map->wall_path[EAST]);
	free(map->wall_path[WEST]);
	free(map->horizontal_plane_path[P_FLOOR]);
	free(map->horizontal_plane_path[P_CEILING]);
	ft_lstclear(&map->spawn, free);
	if (map->map)
		free_string_array(map->map);
}
