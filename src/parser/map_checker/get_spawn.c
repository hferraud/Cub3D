/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_spawn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 04:15:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/13 04:15:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	is_spawn(char c);
static void	add_spawn(size_t line, size_t column, t_map *map);
static int	spawn_error(size_t nb_spawn);

/**
 * @brief Search spawn point in the map and fill map data
 * If an error occurred an error message is display
 * @return 0 on success, -1 otherwise
 */
int	get_spawn_position(t_map *map)
{
	size_t	line;
	size_t	column;
	size_t	nb_spawn;

	line = 0;
	nb_spawn = 0;
	while (map->map[line])
	{
		column = 0;
		while (map->map[line][column])
		{
			if (is_spawn(map->map[line][column]))
			{
				add_spawn(line, column, map);
				nb_spawn++;
			}
			column++;
		}
		line++;
	}
	if (nb_spawn != 1)
		return (spawn_error(nb_spawn));
	return (0);
}

static int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	add_spawn(size_t line, size_t column, t_map *map)
{
	map->spawn.orientation = map->map[line][column];
	map->map[line][column] = '0';
	map->spawn.x = column;
	map->spawn.y = line;
}

static int	spawn_error(size_t nb_spawn)
{
	if (nb_spawn > 1)
		return (parser_error("Too many spawn point\n"));
	return (parser_error("The map does not contain a spawn for the player\n"));
}
