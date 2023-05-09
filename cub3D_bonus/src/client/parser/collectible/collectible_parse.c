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

static void collectible_to_list(t_collectible_list **list, t_map_client *map);
static int	collectible_list_to_array(t_collectible_list *list, t_map_client *map);
static int	cell_parse(size_t row, size_t col, t_map_client *map, t_collectible_list **list);

/**
 * @brief Add all collectible in the map to a linked list
 * @return 0 on success, -1 otherwise
 */
int	collectible_parse(t_map_client *map)
{
	t_collectible_list	*list;

	collectible_to_list(&list, map);
	if (errno)
        return (-1);
	if (collectible_list_to_array(list, map) == -1)
		return (-1);
	collectible_list_clear(list);
	map->collectible_data.collectible_lock = malloc(sizeof(pthread_mutex_t));
	if (map->collectible_data.collectible_lock == NULL)
		return (-1);
	if (pthread_mutex_init(map->collectible_data.collectible_lock, NULL) != 0)
		return (free(map->collectible_data.collectible_lock), -1);
	return (0);
}

/**
 * @brief Convert collectibles to linked list
 * @return The collectible list, NULL if an error occurred
 */
static void collectible_to_list(t_collectible_list **list, t_map_client *map)
{
	size_t			row;
	size_t			col;

	*list = NULL;
	row = 0;
	while (map->map[row])
	{
		col = 0;
		while (map->map[row][col])
		{
			if (cell_parse(row, col, map, list) == -1)
				return ;
			col++;
		}
		row++;
	}
}

/**
 * @brief Convert a collectible list to an array stored in map
 * @return 0 on success, -1 otherwise
 */
static int	collectible_list_to_array(t_collectible_list *list, t_map_client *map)
{
	size_t			size;
	size_t			i;

	size = collectible_list_length(list);
	map->collectible_data.size = size;
	map->collectible_data.collectible = malloc(size * sizeof(t_collectible));
	if (map->collectible_data.collectible == NULL)
		return (perror("collectible_list_to_array()"), -1);
	i = 0;
	while (list)
	{
		map->collectible_data.collectible[i] = collectible_init(list->id, list->pos);
		i++;
		list = list->next;
	}
	return (0);
}

/**
 * @brief Parse the collectible on the current cell
 * @return 0 on success, -1 otherwise
 */
static int	cell_parse(size_t row, size_t col, t_map_client *map, t_collectible_list **list)
{
	t_fvector			pos;
	t_collectible_id	id;

	id = collectible_id_get(map->map[row][col]);
	if (id == UNDEFINED)
		return (0);
	pos = fvector_init(col + 0.5f, row + 0.5f);
	if (collectible_append(list, id, pos) == -1)
	{
		collectible_list_clear(*list);
		return (perror("collectible cell_parse()"), -1);
	}
	map->map[row][col] = FLOOR;
	return (0);
}
