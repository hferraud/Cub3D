/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 03:12:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/17 03:12:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"
#include "raycasting.h"

void	draw_wall(t_cub *cub, int nb_ray)
{
	const int	ray_width = WIN_WIDTH / nb_ray;
	const float	step = PLAYER_FOV / nb_ray;
	const float	theta_end = cub->player->rotation + PLAYER_FOV / 2;
	float		theta;
	float		dist;
	size_t		count;
	int			ceilling_size;
	int			floor_size;

	theta = cub->player->rotation - PLAYER_FOV / 2;
	count = 0;
	while (theta <= theta_end)
	{
		dist = ray_cast(cub, theta);
		ceilling_size = 0.5 * WIN_HEIGHT - tanf(1.0 / 2.0 * theta) * dist;
		floor_size = WIN_HEIGHT - ceilling_size;
		draw_rectangle(&cub->mlx_data->img_data, set_rectangle(set_point(count * ray_width, ceilling_size), set_point((count + 1) * ray_width, floor_size), 0xFF));
		theta += step;
		count++;
	}
}