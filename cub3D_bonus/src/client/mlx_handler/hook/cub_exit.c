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

/**
 * @brief This function allows to free all the memories
 * at the end of the execution of the program
 */
int	cub_exit(t_cub *cub)
{
	mlx_do_key_autorepeaton(cub->mlx_data->mlx_ptr);
	close(cub->server_socket);
	if (cub->thread != 0)
		pthread_join(cub->thread, NULL);
	pthread_mutex_destroy(cub->client_status.status_lock);
	free(cub->client_status.status_lock);
	map_clear(&cub->map);
	mlx_data_destroy(cub->mlx_data);
	player_data_destroy(&cub->player_data);
	exit(0);
}
