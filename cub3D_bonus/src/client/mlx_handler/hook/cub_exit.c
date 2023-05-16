/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:37:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 07:37:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hook.h"
#include "player_data.h"

void	client_status_destroy(pthread_mutex_t *client_status_lock);

/**
 * @brief This function allows to free all the memories
 * at the end of the execution of the program
 */
int	cub_exit(t_cub *cub)
{
	if (cub->mlx_data->mlx_ptr)
	{
		mlx_mouse_show(cub->mlx_data->mlx_ptr, cub->mlx_data->win_ptr);
		mlx_do_key_autorepeaton(cub->mlx_data->mlx_ptr);
	}
	pthread_mutex_lock(cub->client_status.status_lock);
	cub->client_status.status = ERROR;
	pthread_mutex_unlock(cub->client_status.status_lock);
	if (cub->thread != 0)
		pthread_join(cub->thread, NULL);
	close(cub->server_socket);
	client_status_destroy(cub->client_status.status_lock);
	if (cub->enemies_lock)
	{
		pthread_mutex_destroy(cub->enemies_lock);
		free(cub->enemies_lock);
	}
	free(cub->map.collectible_data.collectible);
	map_clear(&cub->map);
	if (cub->mlx_data->mlx_ptr)
		mlx_data_destroy(cub->mlx_data);
	player_data_destroy(&cub->player_data);
	exit(0);
}
