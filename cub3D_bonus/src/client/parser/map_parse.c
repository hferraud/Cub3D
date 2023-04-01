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

static int	map_size_parse(t_map *map, int server_fd);

int map_parse(t_map *map, int server_fd)
{
	size_t	index;

	if (map_size_parse(map, server_fd) == -1)
	{
		write(server_fd, "1", 1);
		return (-1); //CLEAR
	}
	map->map = malloc(sizeof(char *) * map->height + 1);
	if (map->map == NULL)
	{
		write(server_fd, "1", 1);
		return (-1); //CLEAR
	}
	map->map[map->height] = NULL;
	index = 0;
	while (index < map->height)
	{
		map->map[index] = malloc(sizeof(char) * map->width + 1);
		if (map->map[index] == NULL)
		{
			write(server_fd, "1", 1);
			return (-1); //CLEAR
		}
		index++;
	}
	write(server_fd, "0", 1);
	return (0);
}

static int	map_size_parse(t_map *map, int server_fd)
{
	size_t buf;

	buf = 0;
	if (read(server_fd, &buf, sizeof(size_t)) <= 0)
		return (cub_error("Connection with server lost\n"));
	map->height = buf;
	printf("%zu\n", map->height);
	if (read(server_fd, &buf, sizeof(size_t)) <= 0)
		return (cub_error("Connection with server lost\n"));
	map->width = buf;
	return (0);
}