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

static void	draw_wall_band(t_cub *cub, t_ray ray, int screen_x, int start_y, int end_y);
static void mlx_get_wall_stripe(int *stripe, t_sprite wall_sprite, t_vector texture_pos, t_vector screen_pos, int screen_start_y, int screen_end_y);
static void	mlx_put_wall_stripe(t_cub *cub, int *stripe, t_vector screen_pos, int end_y);

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
	t_vector	texture_pos;
	t_vector	screen_pos;
	int			stripe[WIN_HEIGHT];

	wall_sprite = cub->mlx_data->texture_sprite[ray.wall_face];
	if (ray.wall_face == NORTH || ray.wall_face == SOUTH)
		texture_pos.x = (ray.pos.x - (int) ray.pos.x) * wall_sprite.width;
	else
		texture_pos.x = (ray.pos.y - (int) ray.pos.y) * wall_sprite.width;
	screen_pos = vector_init(screen_x, start_y);
	if (screen_pos.y < 0)
		screen_pos.y = 0;
	mlx_get_wall_stripe(stripe, wall_sprite, texture_pos, screen_pos, start_y, end_y);
	mlx_put_wall_stripe(cub, stripe, screen_pos, end_y);
}

static void mlx_get_wall_stripe(int *stripe, t_sprite wall_sprite, t_vector texture_pos, t_vector screen_pos, int screen_start_y, int screen_end_y)
{
	int		wall_height;
	int		i;
	char	*texture_addr;
	float	step;

	wall_height = screen_end_y - screen_start_y;
	step = (float) wall_sprite.height / wall_height;
	if (screen_end_y > WIN_HEIGHT)
		screen_end_y = WIN_HEIGHT;
	texture_addr = wall_sprite.img_data.addr + texture_pos.x * wall_sprite.img_data.bit_ratio;
	i = 0;
	while (screen_pos.y < screen_end_y)
	{
		texture_pos.y = (screen_pos.y - screen_start_y) * step;
		stripe[i] = *(int *) (texture_addr + texture_pos.y * wall_sprite.img_data.line_length);
		screen_pos.y++;
		i++;
	}
}

static void	mlx_put_wall_stripe(t_cub *cub, int *stripe, t_vector screen_pos, int end_y)
{
	char	*img_addr;
	int		i;

	if (end_y > WIN_HEIGHT)
		end_y = WIN_HEIGHT;
	img_addr = cub->mlx_data->img_data.addr;
	img_addr += screen_pos.x * cub->mlx_data->img_data.bit_ratio;
	img_addr += screen_pos.y * cub->mlx_data->img_data.line_length;
	i = 0;
	while (screen_pos.y + i < end_y)
	{
		*(unsigned int *)img_addr = stripe[i];
		img_addr += cub->mlx_data->img_data.line_length;
		i++;
	}
}