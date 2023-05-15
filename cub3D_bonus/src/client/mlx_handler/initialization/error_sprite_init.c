/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_sprite_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 01:05:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/14 01:05:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"

int	error_sprite_init(t_cub *cub)
{
	size_t	index;

	index = 0;
	while (index < NB_TEXTURE)
	{
		free(cub->map.path[index]);
		cub->map.path[index] = NULL;
		if (cub->mlx_data->texture_sprite[index].img_data.img)
			mlx_destroy_image(cub->mlx_data->mlx_ptr,
				cub->mlx_data->texture_sprite[index].img_data.img);
		cub->mlx_data->texture_sprite[index].img_data.img = NULL;
		index++;
	}
	index = 0;
	while (index < NB_COLLECTIBLE)
	{
		if (cub->mlx_data->collectible_sprite[index].img_data.img)
			mlx_destroy_image(cub->mlx_data->mlx_ptr,
				cub->mlx_data->collectible_sprite[index].img_data.img);
		cub->mlx_data->collectible_sprite[index].img_data.img = NULL;
		index++;
	}
	return (cub_error("mlx_xpm_file_to_image() failed\n"));
}
