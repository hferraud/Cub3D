/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_socket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/28 22:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "socket_client.h"
#include "parser_client.h"

static void	print_map(t_map_client map);

int	main(int argc, char **argv)
{
	uint16_t		port;
	int				socket_fd;
	t_map_client	map;

	if (argc != 3)
		return (cub_error("./cub3D IP port\n"));
	port = port_get(argv[2]);
	if (errno)
		return (cub_error("Invalid port\n"));
	socket_fd = socket_client_init(argv[1], port);
	if (socket_fd == -1)
		return (-1);
	parser(&map, socket_fd);
	print_map(map);
	close(socket_fd);
	return (0);
}

static void	print_map(t_map_client map)
{
	size_t	i;

	i = 0;
	while (map.map[i])
	{
		printf("%s\n", map.map[i]);
		i++;
	}
	printf("spawn:\nx: %zu\ny: %zu\nor: %c\n", map.spawn.x, map.spawn.y, map.spawn.orientation);
}
