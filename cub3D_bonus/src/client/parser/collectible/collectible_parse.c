/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 07:08:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/04/29 07:08:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_client.h"

static int	cell_parse(size_t row, size_t col, t_map_client *map);

/**
 * @brief Add all collectible in the map to a linked list
 * @return 0 on success, -1 otherwise
 */
int	collectible_parse(t_map_client *map)
{
	size_t	row;
	size_t	col;

	row = 0;
	col = 0;
	while (map->map[row])
	{
		while (map->map[col])
		{
			cell_parse(row, col, map);
			col++;
		}
		row++;
	}
	return (0);
}

/**
 * @brief Parse the collectible on the current cell
 * @return 0 on success, -1 otherwise
 */
static int	cell_parse(size_t row, size_t col, t_map_client *map)
{
	t_collectible_id	id;
	t_fvector			pos;

	id = collectible_id_get(map->map[row][col]);
	if (id != UNDEFINED)
	{
		pos = fvector_init(col + 0.5f, row + 0.5f);
		if (collectible_append(&map->collectibles, id, pos) == -1)
		{
			collectible_clear(map->collectibles);
			return (-1);
		}
		map->map[row][col] = FLOOR;
	}
	return (0);
}