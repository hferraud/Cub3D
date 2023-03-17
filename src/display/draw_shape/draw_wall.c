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

int	mlx_get_color(void *img_ptr, int x, int y);
static void	draw_wall_band(t_cub *cub, t_ray ray, int screen_x, int start_y, int end_y);

void	draw_wall(t_cub *cub, int x, t_ray ray)
{
	float		dist;
	int			draw_start;
	int			draw_end;
    int         line_height;

	dist = ray.ray_length;
	line_height = WIN_HEIGHT / dist;
	draw_start = -line_height / 2 + WIN_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WIN_HEIGHT / 2;
	if (draw_end >= WIN_HEIGHT)
		draw_end = WIN_HEIGHT - 1;
	draw_wall_band(cub, ray, x, draw_start, draw_end);
}

static void	draw_wall_band(t_cub *cub, t_ray ray, int screen_x, int start_y, int end_y)
{
	t_sprite	wall_sprite;
	t_point 	wall_offset;
//	int			band_length;
	int			screen_y;
	int			color;

	if (ray.wall_face == NORTH)
		wall_sprite = cub->mlx_data->wall[NORTH];
	else if (ray.wall_face == SOUTH)
		wall_sprite = cub->mlx_data->wall[SOUTH];
	else if (ray.wall_face == EAST)
		wall_sprite = cub->mlx_data->wall[EAST];
	else if (ray.wall_face == WEST)
		wall_sprite = cub->mlx_data->wall[WEST];
	wall_offset.y = 0;
	if (ray.wall_face == NORTH || ray.wall_face == SOUTH)
		wall_offset.x = cub->player->pos.x + ray.ray_length / ray.ray_unit_step.x;
	else
		wall_offset.x = cub->player->pos.x + ray.ray_length / ray.ray_unit_step.y;
//	wall_offset.x -= floor(wall_offset.x);
//	band_length = end_y - start_y;
	screen_y = start_y;
	while (screen_y < end_y)
	{
		wall_offset.y = (screen_y / (float) end_y) * (float) wall_sprite.height;
//		printf("band: %d\n", band_length);
//		printf("wall_size: %d %d\noffset: %d %d\n", wall_sprite.width, wall_sprite.height, wall_offset.x, wall_offset.y);
		color = mlx_get_color(wall_sprite.img, wall_offset.x, wall_offset.y);
//		printf("color: %d\nx: %d, y: %d\n", color, screen_x, screen_y);
		mlx_put_pixel(&cub->mlx_data->img_data, screen_x, screen_y, color);
		screen_y++;
	}
}

int	mlx_get_color(void *img_ptr, int x, int y)
{
	int		bit_per_pixel;
	int		size_line;
	int		endian;
	char	*addr;

	addr = mlx_get_data_addr(img_ptr, &bit_per_pixel, &size_line, &endian);
	return (*(unsigned int*)(addr + (y * size_line) + x * bit_per_pixel));
}