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
#include "parser_server.h"
#include "socket_server.h"
#include "server_data.h"

//static void	print_t_map(t_map map);
//static void	print_map(t_map map);
//static void	print_spawn(t_list *head);

int	main(int argc, char **argv)
{
	t_server_data	*server_data;
	t_map			map;
	int				port;
	int				server_fd;

	if (argc != 3)
		return (cub_error("./cub3D_server map.cub port\n"));
	if (parser(argv, &map) == -1)
		return (2);
	server_data = thread_init(&map);
	if (server_data == NULL)
	{
		map_data_clear(&map);
		return (1);
	}
	port = port_get(argv[2]);
	if (port == -1)
	{
		server_data_destroy(server_data);
		cub_error("Invalid port\n");
		return (EINVAL);
	}
	server_fd = socket_init(argv[2], map.nb_spawn);
	if (server_fd == -1)
		return (server_data_destroy(server_data), 1);
	listen_connections(server_fd, server_data);
}

//static void	print_t_map(t_map map)
//{
//	printf("NO: %s\n", map.path[NORTH_ID]);
//	printf("SO: %s\n", map.path[SOUTH_ID]);
//	printf("WE: %s\n", map.path[WEST_ID]);
//	printf("EA: %s\n\n", map.path[EAST_ID]);
//	printf("F: %s\n", map.path[FLOOR_ID]);
//	printf("C: %s\n\n", map.path[CEILING_ID]);
//	printf("D: %s\n\n", map.path[DOOR_ID]);
//	print_spawn(map.spawn);
//	print_map(map);
//}
//
//static void	print_map(t_map map)
//{
//	size_t	i;
//
//	i = 0;
//	while (map.map[i])
//	{
//		printf("%s\n", map.map[i]);
//		i++;
//	}
//}
//
//static void	print_spawn(t_list *head)
//{
//	size_t	count;
//
//	count = 0;
//	while (head)
//	{
//		printf("Spawn %zu\n", count);
//		printf("\tx: %zu\n\ty: %zu\n\torientation: %c\n\n", ((t_spawn *) head->content)->x, ((t_spawn *) head->content)->y, ((t_spawn *) head->content)->orientation);
//		head = head->next;
//		count++;
//	}
//}
