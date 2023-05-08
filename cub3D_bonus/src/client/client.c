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
void		client_status_destroy(pthread_mutex_t *client_status_lock);

int	main(int argc, char **argv)
{
	t_cub		cub;
	t_mlx_data	mlx_data;

	cub.thread = 0;
	client_status_init(&cub.client_status);
	cub.server_socket = socket_client_init(argc, argv);
	if (cub.server_socket == -1)
	{
		client_status_destroy(cub.client_status.status_lock);
		return (1);
	}
	cub.mlx_data = &mlx_data;
	if (cub_init(&cub) == -1)
		return (close(cub.server_socket), 1);
	if (thread_init(&cub) == -1)
		cub_exit(&cub);
	mlx_mouse_hide(cub.mlx_data->mlx_ptr, cub.mlx_data->win_ptr);
	mlx_mouse_move(cub.mlx_data->mlx_ptr, cub.mlx_data->win_ptr,
		WIN_WIDTH / 2, WIN_HEIGHT / 2);
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

void	client_status_destroy(pthread_mutex_t *client_status_lock)
{
	pthread_mutex_destroy(client_status_lock);
	free(client_status_lock);
}
