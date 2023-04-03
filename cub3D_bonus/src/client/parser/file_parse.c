/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:39:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/03 18:39:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_client.h"

static int	filename_parse(char *dest, int server_socket);

int	file_parse(t_map_client *map, int server_socket)
{
	t_texture_id	id;

	id = 0;
	while (id != UNDEFINED_ID)
	{
		if (filename_parse(map->filename[id], server_socket) == -1)
		{
			write(server_socket, SOCK_ERROR, 1);
			return (-1);
		}
		id++;
	}
}

static int	filename_parse(char *dest, int server_socket)
{
	size_t	size;

	if (read(server_socket, &size, sizeof(size_t)) <= 0)
		return (cub_error(SERVER_LOST));
	dest = malloc((size + 1) * sizeof(char));
	if (dest == NULL)
		return (cub_error(NULL));
	if (write(server_socket, SOCK_SUCCESS, 1) == -1)
		return (cub_error(SERVER_LOST));
	if (read(server_socket, dest, size * sizeof(char)) <= 0)
		return (cub_error(SERVER_LOST));
	dest[size] = '\0';
	if (write(server_socket, SOCK_SUCCESS, 1) == -1)
		return (cub_error(SERVER_LOST));
	return (0);
}

/**
 * Send a request to the server if the file is missing
 * @return 0 on success, -1 otherwise
 */
static int	file_request(char *filename, int server_socket)
{
	if (access(filename, R_OK) )
}