/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:21:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/02 19:21:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

void	request_routine(t_cub *cub);

int	thread_init(t_cub *cub)
{
	if (player_data_init(&cub->player_data) == -1)
		return (-1);
	if (pthread_create(&cub->thread, NULL, (void *) request_routine, cub) != 0)
	{
		player_data_destroy(&cub->player_data);
		return (-1);
	}
	return (0);
}