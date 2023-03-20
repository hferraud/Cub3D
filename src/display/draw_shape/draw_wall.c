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

static int	mlx_get_color(t_sprite sprite, int x, int y);
static void	draw_wall_band(t_cub *cub, t_ray ray, int screen_x, int start_y, int end_y);

void	draw_wall(t_cub *cub, int x, t_ray ray)
{
	float	dist;
	int		draw_start;
	int		draw_end;
	int		wall_height;

	dist = ray.ray_length;
	wall_height = WIN_HEIGHT / dist;
	draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
	draw_end = wall_height / 2 + WIN_HEIGHT / 2;
	draw_wall_band(cub, ray, x, draw_start, draw_end);
}

static void	draw_wall_band(t_cub *cub, t_ray ray, int screen_x, int start_y, int end_y)
{
	t_sprite	wall_sprite;
	t_point		wall_offset;
	int			display_height;
	int			screen_y;
	int			color;

	wall_sprite = cub->mlx_data->wall[ray.wall_face];
	wall_offset.y = 0;
	if (ray.wall_face == NORTH || ray.wall_face == SOUTH)
		wall_offset.x = (ray.ray_pos.x - (int) ray.ray_pos.x) * wall_sprite.width;
	else
		wall_offset.x = (ray.ray_pos.y - (int) ray.ray_pos.y) * wall_sprite.width;
	display_height = end_y - start_y;
	screen_y = start_y;
	if (screen_y < 0)
		screen_y = 0;
	while (screen_y < end_y && screen_y < WIN_HEIGHT)
	{
		wall_offset.y = ((screen_y - start_y) / (float) display_height) * (float) wall_sprite.height;
		color = mlx_get_color(wall_sprite, wall_offset.x, wall_offset.y);
		mlx_put_pixel(&cub->mlx_data->img_data, screen_x, screen_y, color);
		screen_y++;
	}
}

static int	mlx_get_color(t_sprite sprite, int x, int y)
{
	t_img_data	sprite_data;

	sprite_data = sprite.img_data;
	return (*(unsigned int*)(sprite_data.addr + (y * sprite_data.line_length) + x * sprite_data.bit_ratio));
}