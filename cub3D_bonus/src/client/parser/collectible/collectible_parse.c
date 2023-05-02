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

static int	cell_parse(size_t row, size_t col, t_map_client *map, t_collectible_list *list);

/**
 * @brief Add all collectible in the map to a linked list
 * @return 0 on success, -1 otherwise
 */
int	collectible_parse(t_map_client *map)
{
	return (0);
}

/**
 * @brief Convert collectibles to linked list
 * @return The collectible list, NULL if an error occurred
 */
static t_collectible_list	*collectible_to_list(t_map_client *map)
{
	t_collectible_list	*list;
	size_t			row;
	size_t			col;

	row = 0;
	while (map->map[row])
	{
		col = 0;
		while (map->map[row][col])
		{
			if (cell_parse(row, col, map, list) == -1)
				return (NULL);
			col++;
		}
		row++;
	}
}

static t_collectible	*collectible_list_to_array(t_collectible_list *list)
{
	t_collectible	*collectible_array;
	size_t			size;

	size = collectible_list_length(list) + 1;
	collectible_array = malloc(size * sizeof(t_collectible));
	if (collectible_array == NULL)
		return (NULL);
}

/**
 * @brief Parse the collectible on the current cell
 * @return 0 on success, -1 otherwise
 */
static int	cell_parse(size_t row, size_t col, t_map_client *map, t_collectible_list *list)
{
	t_fvector			pos;
	t_collectible_id	id;

	id = collectible_id_get(map->map[row][col]);
	if (id == UNDEFINED)
		return (0);
	pos = fvector_init(col + 0.5f, row + 0.5f);
	if (collectible_append(&list, id, pos) == -1)
	{
		collectible_clear(list);
		return (-1);
	}
	map->map[row][col] = FLOOR;
	return (0);
}