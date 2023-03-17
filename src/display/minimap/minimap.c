/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:13:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/14 13:13:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"
#include "raycasting.h"

static void	draw_player(t_cub *cub, int wall_width);
static void draw_player_rotation(t_cub *cub, int wall_width);
static void draw_player_fov(t_cub *cub, int wall_width);
static void	draw_player_view(t_cub *cub, int nb_ray, int wall_width);

void	draw_minimap(t_cub *cub)
{
	int			wall_width;
	size_t		i;
	size_t		j;
	t_rectangle	square;

	if (cub->map->width * WIN_WIDTH > cub->map->height * WIN_HEIGHT)
		wall_width = (int)((float) WIN_WIDTH / (float) cub->map->width);
	else
		wall_width = (int)((float) WIN_HEIGHT / (float) cub->map->height);
	i = 0;
	while (i < cub->map->height)
	{
		j = 0;
		while (cub->map->map[i][j])
		{
			if (cub->map->map[i][j] == WALL || cub->map->map[i][j] == ' ')
			{
				square = set_square(set_point((int) j * wall_width,
							(int) i * wall_width), wall_width, 0x888888);
				draw_rectangle(&cub->mlx_data->img_data, square);
			}
			else if (cub->map->map[i][j] == FLOOR)
			{
				square = set_square(set_point((int) j * wall_width,
											  (int) i * wall_width), wall_width, 0x444444);
				draw_rectangle(&cub->mlx_data->img_data, square);
			}
			j++;
		}
		i++;
	}
	square = set_square(set_point((int) cub->map->spawn.x * wall_width,
				(int) cub->map->spawn.y * wall_width), wall_width, 0x95eb34);
	draw_rectangle(&cub->mlx_data->img_data, square);
	draw_player(cub, wall_width);
}

static void	draw_player(t_cub *cub, int wall_width)
{
	t_rectangle	square;

	square = set_square(set_point((cub->player->pos.x - PLAYER_OFFSET) * wall_width,
								  (cub->player->pos.y - PLAYER_OFFSET) * wall_width), wall_width * 2 * PLAYER_OFFSET, 0x779bf7);
	draw_player_view(cub, 90, wall_width);
	draw_rectangle(&cub->mlx_data->img_data, square);
	draw_player_rotation(cub, wall_width);
	draw_player_fov(cub, wall_width);
}

static void draw_player_rotation(t_cub *cub, int wall_width)
{
	t_point	p_rot;
	t_point	p_pos;

	(void) wall_width;
	p_rot.x = cub->player->pos.x * wall_width + cosf(cub->player->rotation) * wall_width;
	p_rot.y = cub->player->pos.y * wall_width + sinf(cub->player->rotation) * wall_width;
	p_pos.x = cub->player->pos.x * wall_width;
	p_pos.y = cub->player->pos.y * wall_width;
	draw_line(&cub->mlx_data->img_data, p_pos, p_rot, 0x222222);
}


static void draw_player_fov(t_cub *cub, int wall_width)
{
	t_point	p_fovr;
	t_point	p_fovl;
	t_point	p_pos;

	p_pos.x = cub->player->pos.x * wall_width;
	p_pos.y = cub->player->pos.y * wall_width;
	p_fovr.x = p_pos.x + cosf(cub->player->rotation + PLAYER_FOV / 2) * wall_width;
	p_fovr.y = p_pos.y + sinf(cub->player->rotation + PLAYER_FOV / 2) * wall_width;
	p_fovl.x = p_pos.x + cosf(cub->player->rotation - PLAYER_FOV / 2) * wall_width;
	p_fovl.y = p_pos.y + sinf(cub->player->rotation - PLAYER_FOV / 2) * wall_width;
	draw_line(&cub->mlx_data->img_data, p_pos, p_fovr, 0xFFFFFF);
	draw_line(&cub->mlx_data->img_data, p_pos, p_fovl, 0xFFFFFF);
}

static void	draw_player_view(t_cub *cub, int nb_ray, int wall_width)
{
	float	theta;
	float	theta_max;
	float	theta_step;
	float	dist;
	t_ray	ray;
	t_point	p_pos;
	t_point	collision_point;


	theta_step = PLAYER_FOV / nb_ray;
	p_pos.x = cub->player->pos.x * wall_width;
	p_pos.y = cub->player->pos.y * wall_width;
	theta = cub->player->rotation - PLAYER_FOV / 2;
	theta_max = cub->player->rotation + PLAYER_FOV / 2;
	while (theta <= theta_max)
	{
		ray = ray_cast(cub, theta);
		dist = ray.ray_length;
		if (dist != 0)
		{
			collision_point.x = p_pos.x + cos(theta) * dist * wall_width;
			collision_point.y = p_pos.y + sin(theta) * dist * wall_width;
			draw_line(&cub->mlx_data->img_data, p_pos, collision_point, 0xFF00FF);
		}
		theta += theta_step;
	}
}
