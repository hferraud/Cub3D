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
#include "parser_bonus.h"

static int	is_spawn(char c);
static int	add_spawn(size_t line, size_t column, t_map *map);
static int	spawn_error(size_t nb_spawn);

/**
 * @brief Search spawn point in the map and fill map data
 * If an error occurred an error message is displayed
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
				if (add_spawn(line, column, map) == -1)
					return (-1);
				nb_spawn++;
			}
			column++;
		}
		line++;
	}
	if (nb_spawn == 0 || nb_spawn > PLAYER_LIMIT)
		return (spawn_error(nb_spawn));
	return (0);
}

static int	add_spawn(size_t line, size_t column, t_map *map)
{
	t_spawn	*new_spawn;
	t_list	*node;

	new_spawn = (t_spawn *) malloc(sizeof(t_spawn));
	if (new_spawn == NULL)
		return (cub_error("Malloc failed\n"));
	new_spawn->orientation = map->map[line][column];
	new_spawn->x = column;
	new_spawn->y = line;
	map->map[line][column] = '0';
	node = ft_lstnew(new_spawn);
	if (node == NULL)
	{
		free(new_spawn);
		return (cub_error("Malloc failed\n"));
	}
	ft_lstadd_front(&map->spawn, node);
	return (0);
}

static int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	spawn_error(size_t nb_spawn)
{
	if (nb_spawn > PLAYER_LIMIT)
		return (cub_error("Too many spawn point\n"));
	return (cub_error("The map does not contain a spawn for the player\n"));
}
