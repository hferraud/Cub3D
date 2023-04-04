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
#include "parser.h"


double		fps_average(int fps, int get_average);

/**
 * @brief This function allows to free all the memories
 * at the end of the execution of the program
 */
int	cub_exit(t_cub *cub)
{
	mlx_do_key_autorepeaton(cub->mlx_data->mlx_ptr);
	map_data_clear(cub->map);
	mlx_data_destroy(cub->mlx_data);
	//TODO: Remove fps average in mandatory part
	printf("fps average: %f\n", fps_average(0, 1));
	exit(0);
}
