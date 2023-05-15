/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/01 15:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_client.h"

static int	map_size_parse(t_map_client *map, int server_socket);
static int	map_content_parse(t_map_client *map, int server_socket);
static int	map_spawn_parse(t_map_client *map, int server_socket);
static int	map_init(t_map_client *map);

int	map_parse(t_map_client *map, int server_socket)
{
	map->map = NULL;
	map->collectible_data.collectible = NULL;
	ft_bzero(map->path, sizeof(char *) * 7);
	if (map_size_parse(map, server_socket) == -1)
		return (-1);
	if (map_init(map) == -1)
		return (-1);
	if (write(server_socket, "0", 1) == -1)
		return (cub_error(NULL));
	if (map_content_parse(map, server_socket) == -1)
		return (-1);
	if (write(server_socket, "0", 1) == -1)
		return (cub_error(NULL));
	if (map_spawn_parse(map, server_socket) == -1)
		return (-1);
	if (write(server_socket, "0", 1) == -1)
		return (cub_error(NULL));
	return (0);
}

static int	map_size_parse(t_map_client *map, int server_socket)
{
	size_t	buf;

	buf = 0;
	if (read(server_socket, &buf, sizeof(size_t)) <= 0)
	{
		printf("No more spawns available\n");
		return (-1);
	}
	printf("Loading map size\n");
	map->height = buf;
	if (read(server_socket, &buf, sizeof(size_t)) <= 0)
		return (cub_error(SERVER_LOST));
	map->width = buf;
	return (0);
}

static int	map_content_parse(t_map_client *map, int server_socket)
{
	size_t	index;

	printf("Loading map content\n");
	index = 0;
	while (index < map->height)
	{
		if (read(server_socket, map->map[index], map->width) <= 0)
			return (cub_error(SERVER_LOST));
		map->map[index][map->width] = '\0';
		index++;
	}
	return (0);
}

static int	map_spawn_parse(t_map_client *map, int server_socket)
{
	printf("Loading map spawn\n");
	if (read(server_socket, &map->spawn.x, sizeof(size_t)) <= 0)
		return (cub_error(SERVER_LOST));
	if (read(server_socket, &map->spawn.y, sizeof(size_t)) <= 0)
		return (cub_error(SERVER_LOST));
	if (read(server_socket, &map->spawn.orientation, sizeof(char)) <= 0)
		return (cub_error(SERVER_LOST));
	return (0);
}

static int	map_init(t_map_client *map)
{
	size_t	index;

	printf("Initializing map\n");
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (map->map == NULL)
		return (cub_error(NULL));
	map->map[map->height] = NULL;
	index = 0;
	while (index < map->height)
	{
		map->map[index] = malloc(sizeof(char) * (map->width + 1));
		if (map->map[index] == NULL)
			return (free_string_array(map->map), cub_error(NULL));
		index++;
	}
	map->map_lock = malloc(sizeof(pthread_mutex_t));
	if (map->map_lock == NULL)
		return (free_string_array(map->map), cub_error(NULL));
	if (pthread_mutex_init(map->map_lock, NULL) != 0)
	{
		free(map->map_lock);
		return (free_string_array(map->map), cub_error(NULL));
	}
	return (0);
}
