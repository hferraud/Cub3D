/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:41:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/09 19:41:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static void	print_map(t_map map);

int	main(int argc, char **argv)
{
	t_map	map;

	if (parser(argc, argv, &map) == -1)
		return (2);
	printf("NO: %s\n", (char *)map.wall.wall[NORTH]);
	printf("SO: %s\n", (char *)map.wall.wall[SOUTH]);
	printf("WE: %s\n", (char *)map.wall.wall[WEST]);
	printf("EA: %s\n\n", (char *)map.wall.wall[EAST]);
	printf("F: %d,%d,%d\n", map.floor_color >> 16, map.floor_color >> 8 & 255, map.floor_color & 255);
	printf("C: %d,%d,%d\n\n", map.ceiling_color >> 16, map.ceiling_color >> 8 & 255, map.ceiling_color & 255);
	printf("Spawn: %zu, %zu orientation: %c\n\n", map.spawn.x, map.spawn.y, map.spawn.orientation);
	print_map(map);
	clear_map_data(&map);
	return (0);
}

static void	print_map(t_map map)
{
	size_t	i;

	i = 0;
	while (map.map[i])
	{
		printf("%s\n", map.map[i]);
		i++;
	}
}
