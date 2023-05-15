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

static void	draw_wall_band(t_cub *cub, t_ray ray, t_draw_param dp);
static void	mlx_get_wall_stripe(int *stripe, t_draw_param dp);
static void	mlx_put_wall_stripe(t_cub *cub, const int *stripe, t_draw_param dp);

void	draw_wall(t_cub *cub, int screen_x, t_ray ray)
{
	t_draw_param	dp;

	dp.screen.x = screen_x;
	dp.height = WIN_HEIGHT / ray.length;
	dp.draw_start.y = WIN_HEIGHT / 2 - dp.height / 2;
	dp.draw_end.y = WIN_HEIGHT / 2 + dp.height / 2;
	draw_wall_band(cub, ray, dp);
}

static void	draw_wall_band(t_cub *cub, t_ray ray, t_draw_param dp)
{
	int			stripe[WIN_HEIGHT];

	if (ray.is_door)
		dp.sprite = cub->mlx_data->texture_sprite[DOOR_ID];
	else
		dp.sprite = cub->mlx_data->texture_sprite[ray.wall_face];
	if (ray.wall_face == NORTH || ray.wall_face == SOUTH)
		dp.texture.x = (ray.pos.x - (int) ray.pos.x) * dp.sprite.width;
	else
		dp.texture.x = (ray.pos.y - (int) ray.pos.y) * dp.sprite.width;
	dp.screen.y = dp.draw_start.y;
	if (dp.screen.y < 0)
		dp.screen.y = 0;
	mlx_get_wall_stripe(stripe, dp);
	mlx_put_wall_stripe(cub, stripe, dp);
}

static void	mlx_get_wall_stripe(int *stripe, t_draw_param dp)
{
	char	*texture_addr;
	float	step;
	int		i;

	step = (float) dp.sprite.height / dp.height;
	texture_addr = dp.sprite.img_data.addr
		+ dp.texture.x * dp.sprite.img_data.bit_ratio;
	i = 0;
	while (dp.screen.y < dp.draw_end.y && dp.screen.y < WIN_HEIGHT)
	{
		dp.texture.y = (dp.screen.y - dp.draw_start.y) * step;
		stripe[i] = *(int *)(texture_addr
				+ dp.texture.y * dp.sprite.img_data.line_length);
		dp.screen.y++;
		i++;
	}
}

static void	mlx_put_wall_stripe(t_cub *cub, const int *stripe, t_draw_param dp)
{
	char	*img_addr;
	int		i;

	if (dp.draw_end.y > WIN_HEIGHT)
		dp.draw_end.y = WIN_HEIGHT;
	img_addr = cub->mlx_data->img_data.addr;
	img_addr += dp.screen.x * cub->mlx_data->img_data.bit_ratio;
	img_addr += dp.screen.y * cub->mlx_data->img_data.line_length;
	i = 0;
	while (dp.screen.y + i < dp.draw_end.y)
	{
		*(int *)img_addr = stripe[i];
		img_addr += cub->mlx_data->img_data.line_length;
		i++;
	}
}
