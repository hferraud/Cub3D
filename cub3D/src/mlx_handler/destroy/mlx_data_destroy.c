/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_data_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 03:01:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 03:01:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"

#ifdef __gnu_linux__

void	mlx_data_destroy(t_mlx_data *mlx_data)
{
	wall_sprite_destroy(mlx_data);
	if (mlx_data->img_data.img)
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_data.img);
	if (mlx_data->win_ptr)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	if (mlx_data->mlx_ptr)
	{
		mlx_destroy_display(mlx_data->mlx_ptr);
		free(mlx_data->mlx_ptr);
	}
}

#else

void	mlx_data_destroy(t_mlx_data *mlx_data)
{
	wall_sprite_destroy(mlx_data);
	if (mlx_data->img_data.img)
		mlx_destroy_image(mlx_data->mlx_ptr, mlx_data->img_data.img);
	if (mlx_data->win_ptr)
		mlx_destroy_window(mlx_data->mlx_ptr, mlx_data->win_ptr);
	if (mlx_data->mlx_ptr)
		free(mlx_data->mlx_ptr);
}

#endif
