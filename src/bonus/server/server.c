/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:10:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/24 15:10:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_bonus.h"

static void	print_t_map(t_map map);
static void	print_map(t_map map);
static void	print_spawn(t_list *head);

int	main(int argc, char **argv)
{
	t_map	map;

	if (parser(argc, argv, &map) == -1)
		return (2);
	//TODO: Add parse port for the server
	print_t_map(map);
	map_data_clear(&map);
}

static void	print_t_map(t_map map)
{
	printf("NO: %s\n", (char *)map.wall_path[NORTH]);
	printf("SO: %s\n", (char *)map.wall_path[SOUTH]);
	printf("WE: %s\n", (char *)map.wall_path[WEST]);
	printf("EA: %s\n\n", (char *)map.wall_path[EAST]);
	printf("F: %s\n", map.horizontal_plane_path[P_FLOOR]);
	printf("C: %s\n\n", map.horizontal_plane_path[P_CEILING]);
	printf("D: %s\n\n", map.door_path);
	print_spawn(map.spawn);
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

static void	print_spawn(t_list *head)
{
	size_t	count;

	count = 0;
	while (head)
	{
		printf("Spawn %zu\n", count);
		printf("\tx: %zu\n\ty: %zu\n\torientation: %c\n\n", ((t_spawn *) head->content)->x, ((t_spawn *) head->content)->y, ((t_spawn *) head->content)->orientation);
		head = head->next;
		count++;
	}
}
