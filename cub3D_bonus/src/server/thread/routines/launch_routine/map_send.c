/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:29:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/01 15:29:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

static int map_size_send(int client_fd, size_t height, size_t width);

int	map_send(int client_fd, t_launch_data *launch_data, t_spawn *spawn)
{
	(void) spawn;
	if (map_size_send(client_fd, launch_data->map->height, launch_data->map->width) == -1)
		return (-1);
	return (0);
}

static int map_size_send(int client_fd, size_t height, size_t width)
{
	char	buf;

	if (write(client_fd, &height, sizeof(size_t)) == -1
		|| write(client_fd, &width, sizeof(size_t)) == -1
		|| read(client_fd, &buf, sizeof(char)) <= 0)
		return (cub_error("Connection with client lost\n"));
	if (buf == '1')
		return (cub_error("Error in client\n"));
	else
		printf("Map size send\n");
	return (0);
}

//static int	map_content_send(int client_fd, t_launch_data *launch_data)
//{
//
//}