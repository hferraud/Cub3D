/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 02:55:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/12 02:55:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_bonus.h"

static int	set_path(char **sprite, char *sprite_path);

/**
 * @brief Get the path associated with a wall texture and add it to map struct
 * @return 0 on success, -1 otherwise
 */
int	parse_path(char *line, t_content_type type, t_map *map)
{
	char	*sprite_path;

	while (*line && *line == ' ')
		line++;
	if (*line == '\0')
		return (cub_error("File name is missing\n"));
	sprite_path = ft_substr(line, 0, ft_strlen(line) - 1);
	if (sprite_path == NULL)
		return (cub_error(NULL));
	if (type == NORTH_ID)
		return (set_path(&map->wall_path[NORTH], sprite_path));
	else if (type == SOUTH_ID)
		return (set_path(&map->wall_path[SOUTH], sprite_path));
	else if (type == WEST_ID)
		return (set_path(&map->wall_path[WEST], sprite_path));
	else if (type == EAST_ID)
		return (set_path(&map->wall_path[EAST], sprite_path));
	else if (type == FLOOR_ID)
		return (set_path(&map->horizontal_plane_path[P_FLOOR], sprite_path));
	else if (type == CEILING_ID)
		return (set_path(&map->horizontal_plane_path[P_CEILING], sprite_path));
	else if (type == DOOR_ID)
		return (set_path(&map->door_path, sprite_path));
	return (0);
}

/**
 * @brief Set a t_wall path, free wall path if an error occurred
 * @return 0 on success, -1 otherwise
 */
static int	set_path(char **sprite, char *sprite_path)
{
	if (*sprite != NULL)
	{
		free(sprite_path);
		return (cub_error("Duplicate entry detected\n"));
	}
	*sprite = sprite_path;
	return (0);
}
