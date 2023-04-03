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

int parser(t_map_client *map, int server_socket)
{
	int fd;

	if (map_parse(map, server_socket) == -1)
	{
		write(server_socket, "1", 1);
		return (-1);
	}
	fd = open(DIR_SPRITE, O_DIRECTORY);
	if (fd == -1)
	{
		if (mkdir(DIR_SPRITE, 0755) == -1)
			return (perror("mkdir()"), -1);
	}
	else
		close(fd);
	if (file_parse(map, server_socket) == -1)
	{
		write(server_socket, "1", 1);
		return (-1);
	}
	return (0);
}
