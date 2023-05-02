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

static int	cub_init(t_cub *cub);
static int	client_status_init(t_client_status *client_status);

int	main(int argc, char **argv)
{
	t_cub		cub;
	t_mlx_data	mlx_data;

	cub.thread = 0;
	client_status_init(&cub.client_status);
	cub.server_socket = socket_client_init(argc, argv);
	//TODO: do cub_exit on failure
	if (cub.server_socket == -1)
		return (1);
	cub.mlx_data = &mlx_data;
	player_pos_init(&cub);
	if (cub_init(&cub) == -1)
		return (close(cub.server_socket), 1);
	if (thread_init(&cub) == -1)
		//TODO: do cub_exit on failure
		return (1);
	mlx_loop_hook(cub.mlx_data->mlx_ptr, render_frame, &cub);
	mlx_loop(cub.mlx_data->mlx_ptr);
}

static int	cub_init(t_cub *cub)
{
	if (parser(&cub->map, cub->server_socket) == -1)
		return (-1);
	if (mlx_data_init(cub) == -1)
		return (-1);
	player_pos_init(cub);
	return (0);
}

static int	client_status_init(t_client_status *client_status)
{
	client_status->status_lock = malloc(sizeof(pthread_mutex_t));
	if (client_status->status_lock == NULL)
		return (-1);
	if (pthread_mutex_init(client_status->status_lock, NULL) != 0)
	{
		free(client_status->status_lock);
		return (-1);
	}
	client_status->status = RUNNING;
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
