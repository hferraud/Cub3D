/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:22:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/01 15:22:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_client.h"

static void	map_preset(t_map *map);

int parser(t_map *map, int server_fd)
{
	map_preset(map);
	map_parse(map, server_fd);
	return (0);
}

static void	map_preset(t_map *map)
{
	map->map = NULL;
	map->spawn = NULL;
	ft_bzero(map->path, sizeof(char *) * 7);
}