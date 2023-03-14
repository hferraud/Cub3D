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
#include "mlx_handler.h"

void	print_t_map(t_map map);
static void	print_map(t_map map);

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (parser(argc, argv, &cub.map) == -1)
		return (2);
	if (mlx_data_init(&cub) == -1)
		return (clear_map_data(&cub.map), 1);
	clear_map_data(&cub.map);
	mlx_data_destroy(&cub.mlx_data);
	return (0);
}

void	print_t_map(t_map map)
{
	printf("NO: %s\n", (char *)map.wall_path[NORTH]);
	printf("SO: %s\n", (char *)map.wall_path[SOUTH]);
	printf("WE: %s\n", (char *)map.wall_path[WEST]);
	printf("EA: %s\n\n", (char *)map.wall_path[EAST]);
	printf("F: %d,%d,%d\n", map.floor_color >> 16, map.floor_color >> 8 & 255, map.floor_color & 255);
	printf("C: %d,%d,%d\n\n", map.ceiling_color >> 16, map.ceiling_color >> 8 & 255, map.ceiling_color & 255);
	printf("Spawn: %zu, %zu orientation: %c\n\n", map.spawn.x, map.spawn.y, map.spawn.orientation);
	print_map(map);
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
