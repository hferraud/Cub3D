/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:16:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/03/11 20:16:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_server.h"

static t_texture_id		get_content_type(const char *line);
static int				parse_map_data_router(char *line, t_map *map);
static int				is_preset_complete(t_map *map);

/**
 * @brief Parse the map data in the .cub file
 * @return Return 0 on success, -1 otherwise
 */
int	parse_map_data(int map_fd, t_map *map)
{
	char		*line;

	line = get_next_line(map_fd);
	while (line)
	{
		if (*line != '\n')
			if (parse_map_data_router(line, map) == -1)
				return (free(line), -1);
		free(line);
		if (!is_preset_complete(map))
			line = get_next_line(map_fd);
		else
			line = NULL;
	}
	if (errno)
		return (cub_error(NULL));
	return (0);
}

/**
 * @brief Choose to call parse_wall or parse_horizontal_plane
 * @return Return 0 on success, -1 otherwise
 */
static int	parse_map_data_router(char *line, t_map *map)
{
	t_texture_id	content_id;

	content_id = get_content_type(line);
	if (content_id == UNDEFINED_ID)
		return (cub_error("Undefined content\n"));
	else
		return (parse_path(line + 2, content_id, map));
}

/**
 * @return the type of the content, or UNDEFINED if is not a valid content
 */
static t_texture_id	get_content_type(const char *line)
{
	int						i;
	int						j;
	const char				*content_id[] = {"NO", "SO", "WE", "EA", "D", "F",
		"C", NULL};

	i = 0;
	while (content_id[i])
	{
		j = 0;
		while (content_id[i][j] && content_id[i][j] == line[j] && line[j])
			j++;
		if (content_id[i][j] == '\0' && line[j] == ' ')
			return (i);
		i++;
	}
	return (UNDEFINED_ID);
}

static int	is_preset_complete(t_map *map)
{
	if (map->path[NORTH_ID] && map->path[SOUTH_ID] && map->path[WEST_ID]
		&& map->path[EAST_ID] && map->path[DOOR_ID] && map->path[FLOOR_ID]
		&& map->path[CEILING_ID])
		return (1);
	return (0);
}
