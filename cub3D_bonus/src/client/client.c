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
#include "cub.h"

int		render_frame(t_cub *cub);
void	player_pos_init(t_cub *cub);

static int	cub_init(t_cub *cub, int server_socket);

int	main(int argc, char **argv)
{
	t_cub		cub;
	t_mlx_data	mlx_data;

	cub.server_socket = socket_client_init(argc, argv);
	if (cub.server_socket == -1)
		return (1);
	cub.mlx_data = &mlx_data;
	player_pos_init(&cub);
	if (cub_init(&cub, cub.server_socket) == -1)
		return (close(cub.server_socket), 1);
	mlx_loop_hook(cub.mlx_data->mlx_ptr, render_frame, &cub);
	mlx_loop(cub.mlx_data->mlx_ptr);
}

static int	cub_init(t_cub *cub, int server_socket)
{
	if (parser(&cub->map, server_socket) == -1)
		return (-1);
	if (mlx_data_init(cub) == -1)
		return (-1);
	player_pos_init(cub);
	return (0);
}

//static void	print_map(t_map_client map)
//{
//	size_t	i;
//
//	i = 0;
//	while (map.map[i])
//	{
//		printf("%s\n", map.map[i]);
//		i++;
//	}
//	printf("spawn:\nx: %zu\ny: %zu\nor: %c\n", map.spawn.x, map.spawn.y, map.spawn.orientation);
//}
