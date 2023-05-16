/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_sprite_destroy_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 09:54:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/16 09:54:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"

void	destroy_sprite(void *mlx_ptr, t_sprite *sprite)
{
	if (sprite->img_data.img)
	{
		mlx_destroy_image(mlx_ptr, sprite->img_data.img);
		sprite->img_data.img = NULL;
	}
}