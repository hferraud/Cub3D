/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:22:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 11:22:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hook.h"

static void	display_key_press(int key_press[MAX_KEY]);

int	render_frame(t_cub *cub)
{
	display_key_press(cub->mlx_data.key_press);
	mlx_put_image_to_window(cub->mlx_data.mlx_ptr, cub->mlx_data.win_ptr,
		cub->mlx_data.img_data.img, 0, 0);
	return (0);
}

static void	display_key_press(int key_press[MAX_KEY])
{
	size_t	index;

	index = 0;
	while (index < MAX_KEY)
	{
		if (key_press[index] != -1)
			printf("key press: %d\n", key_press[index]);
		index++;
	}
}
