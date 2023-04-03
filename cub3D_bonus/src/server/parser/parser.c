/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:42:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/09 19:42:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_server.h"

/**
 * @brief Parse the map file
 * @return Return 0 on success, -1 otherwise
 */
int	parser(char **argv, t_map *map)
{
	int		map_fd;
	//TODO: open each file for check if they exist (No directory)

	if (!is_valid_filename(argv[1]))
		return (cub_error("Invalid filename\n"));
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd == -1)
		return (cub_error(NULL));
	init_map_data(map);
	if (parse_map_data(map_fd, map) == -1
		|| parse_map(map_fd, map) == -1)
	{
		close(map_fd);
		return (map_data_clear(map), -1);
	}
	close(map_fd);
	if (get_spawn_position(map) == -1
		|| !is_valid_map(map->map))
		return (map_data_clear(map), -1);
	return (0);
}
