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
static void	mlx_get_wall_stripe(t_cub *cub, t_sprite wall_sprite, int texture_x, int screen_x, int screen_start_y, int screen_end_y);

void	draw_wall(t_cub *cub, int x, t_ray ray)
{
	float	dist;
	int		draw_start;
	int		draw_end;
	int		wall_height;

	dist = ray.length;
	wall_height = WIN_HEIGHT / dist;
	draw_start = -wall_height / 2 + WIN_HEIGHT / 2;
	draw_end = wall_height / 2 + WIN_HEIGHT / 2;
	draw_wall_band(cub, ray, x, draw_start, draw_end);
}

static void	draw_wall_band(t_cub *cub, t_ray ray, int screen_x, int start_y, int end_y)
{
	t_sprite	wall_sprite;
	t_vector	texture;

	wall_sprite = cub->mlx_data->wall[ray.wall_face];
	if (ray.wall_face == NORTH || ray.wall_face == SOUTH)
		texture.x = (ray.pos.x - (int) ray.pos.x) * wall_sprite.width;
	else
		texture.x = (ray.pos.y - (int) ray.pos.y) * wall_sprite.width;
	mlx_get_wall_stripe(cub, wall_sprite, texture.x, screen_x, start_y, end_y);
}

static void	mlx_get_wall_stripe(t_cub *cub, t_sprite wall_sprite, int texture_x, int screen_x, int screen_start_y, int screen_end_y)
{
	int		wall_height;
	int		texture_y;
	int		screen_y;
	int		color;
	float	step;

	wall_height = screen_end_y - screen_start_y;
	step = wall_height / (float) wall_sprite.height;
	if (screen_start_y < 0)
		screen_start_y = 0;
	if (screen_end_y > WIN_HEIGHT)
		screen_end_y = WIN_HEIGHT;
	screen_y = screen_start_y;
	printf("texture height: %d\n", wall_sprite.height);
	while (screen_y < screen_end_y)
	{
		texture_y = (int) (screen_y * step + 0.5f);
		printf("texture: %d %d\n", texture_x, texture_y);
		color = mlx_get_color(wall_sprite, texture_x, texture_y);
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