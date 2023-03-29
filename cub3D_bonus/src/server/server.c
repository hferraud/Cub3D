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

static void	print_t_map(t_map map);
static void	print_map(t_map map);
static void	print_spawn(t_list *head);

int	main(int argc, char **argv)
{
	t_map	map;
	int		port;
	int		server_socket_fd;
	int		client_socket_fd;

	if (argc != 3)
		return (cub_error("./cub3D_server map.cub port\n"));
	if (parser(argv, &map) == -1)
		return (2);
	print_t_map(map);
	port = port_get(argv[2]);
	if (port == -1)
	{
		map_data_clear(&map);
		cub_error("Invalid port\n");
		return (EINVAL);
	}
	server_socket_fd = socket_init(argv[2], ft_lstsize(map.spawn));
	if (server_socket_fd == -1)
		return (map_data_clear(&map), 1);
	client_socket_fd = client_accept(server_socket_fd);
	if (client_socket_fd == -1)
	{
		close(server_socket_fd);
		map_data_clear(&map);
		return (1);
	}
	close(server_socket_fd);
	close(client_socket_fd);
	map_data_clear(&map);
}

static void	print_t_map(t_map map)
{
	printf("NO: %s\n", map.path[NORTH_ID]);
	printf("SO: %s\n", map.path[SOUTH_ID]);
	printf("WE: %s\n", map.path[WEST_ID]);
	printf("EA: %s\n\n", map.path[EAST_ID]);
	printf("F: %s\n", map.path[FLOOR_ID]);
	printf("C: %s\n\n", map.path[CEILING_ID]);
	printf("D: %s\n\n", map.path[DOOR_ID]);
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
