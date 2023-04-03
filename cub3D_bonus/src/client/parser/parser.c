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
	if (map_parse(map, server_socket) == -1)
	{
		//TODO create dir asset if it does not exist
		write(server_socket, "1", 1);
		return (-1);
	}
	if (file_parse(map, server_socket) == -1)
	{
		write(server_socket, "1", 1);
		return (-1);
	}
	return (0);
}
