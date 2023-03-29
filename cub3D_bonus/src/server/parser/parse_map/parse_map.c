/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:33:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/12 06:33:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_server.h"

static int	map_to_list(int map_fd, t_list **map_list);
static int	list_to_map(t_list *map_list, t_map *map);
static int	init_map(size_t map_size, size_t row_size, t_map *map);
static void	init_map_row(char *row_dst, const char *row_src, size_t row_size);

/**
 * @brief Parse the map in the .cub file
 * @return Return 0 on success, -1 otherwise
 */
int	parse_map(int map_fd, t_map *map)
{
	t_list	*map_list;

	map_list = NULL;
	if (map_to_list(map_fd, &map_list) == -1)
		return (-1);
	if (!is_valid_map_list(map_list))
	{
		ft_lstclear(&map_list, free);
		return (cub_error("Map contain an invalid character\n"));
	}
	if (list_to_map(map_list, map) == -1)
	{
		ft_lstclear(&map_list, free);
		return (-1);
	}
	ft_lstclear(&map_list, free);
	return (0);
}

/**
 * @brief Return a list containing the map from the map_fd.
 * Every map row validity is checked with is_valid_map_row() function
 * @return 0 on success, -1 otherwise
 */
static int	map_to_list(int map_fd, t_list **map_list)
{
	t_list	*elem;
	char	*line;

	line = skip_empty_line(map_fd);
	if (errno)
		return (cub_error(NULL));
	if (line == NULL)
		return (cub_error("Map input is missing\n"));
	while (line && *line != '\n')
	{
		elem = ft_lstnew(line);
		if (elem == NULL)
		{
			ft_lstclear(map_list, free);
			return (free(line), cub_error(NULL));
		}
		ft_lstadd_front(map_list, elem);
		line = get_next_line(map_fd);
	}
	if (line && *line == '\n')
		free(line);
	ft_lstrev(map_list);
	return (0);
}

/**
 * @brief Convert a the map from t_list to t_map.map
 * @return Return 0 on success, -1 if an error occurred
 */
static int	list_to_map(t_list *map_list, t_map *map)
{
	size_t	i;

	map->height = ft_lstsize(map_list);
	map->width = get_max_row_size(map_list);
	if (init_map(map->height, map->width, map) == -1)
		return (-1);
	i = 0;
	while (map_list)
	{
		init_map_row(map->map[i], (char *)map_list->content, map->width);
		map_list = map_list->next;
		i++;
	}
	return (0);
}

/**
 * @brief Allocate space for the map
 * @return Return 0 on success, -1 otherwise and print error message
 */
static int	init_map(size_t map_size, size_t row_size, t_map *map)
{
	size_t	i;

	map->map = malloc(sizeof (char *) * (map_size + 1));
	if (map->map == NULL)
		return (cub_error(NULL));
	i = 0;
	while (i < map_size)
	{
		map->map[i] = malloc(sizeof (char) * (row_size + 1));
		if (map->map[i] == NULL)
		{
			while (i > 0)
			{
				free(map->map[i - 1]);
				i--;
			}
			free(map->map);
			return (cub_error(NULL));
		}
		i++;
	}
	map->map[i] = NULL;
	return (0);
}

/**
 * @brief Copy content of row_src to row_src with correct format
 */
static void	init_map_row(char *row_dst, const char *row_src, size_t row_size)
{
	size_t	i;

	i = 0;
	while (row_src[i] && row_src[i] != '\n')
	{
		row_dst[i] = row_src[i];
		i++;
	}
	while (i < row_size)
	{
		row_dst[i] = ' ';
		i++;
	}
	row_dst[i] = '\0';
}
