/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_sprite_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:10:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 02:10:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"

void	wall_sprite_destroy(t_mlx_data *mlx_data)
{
	size_t	index;

	index = 0;
	while (index < 4)
	{
		if (mlx_data->wall[index].img_data.img)
		{
			mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->wall[index].img_data.img);
			mlx_data->wall[index].img_data.img = NULL;
		}
		index++;
	}
}
