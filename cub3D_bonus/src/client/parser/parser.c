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

int	parser(t_map_client *map, int server_socket)
{
	int	asset_dir;
    int var;
	//TODO clear on error

	if (map_parse(map, server_socket) == -1)
	{
        var = write(server_socket, "1", 1);
        (void)var;
		return (-1);
	}
	asset_dir = open(DIR_SPRITE, O_DIRECTORY);
	if (asset_dir == -1)
		return (cub_error("Asset directory doesn't exist\n"));
	else
		close(asset_dir);
	if (file_parse(map, server_socket) == -1)
	{
        var = write(server_socket, "1", 1);
        (void)var;
		return (-1);
	}
	if (collectible_parse(map) == -1)
		return (-1);
	return (0);
}
