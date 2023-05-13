/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:35:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/14 12:35:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef DRAW_H
# define DRAW_H

# include <sys/param.h>
# include <math.h>
# include "mlx_handler.h"

typedef struct s_rectangle	t_rectangle;
typedef struct s_draw_param	t_draw_param;
typedef struct s_ray		t_ray;

struct s_rectangle
{
	t_vector	start;
	t_vector	end;
	int			color;
};

struct s_draw_param
{
	int			color;
	int			height;
	int			width;
	t_vector	screen;
	t_vector	texture;
	t_vector	draw_start;
	t_vector	draw_end;
	t_sprite	sprite;
};

/* --- DRAW FUNCTIONS --- */

void		mlx_put_pixel(t_img_data *img_data, int x, int y, int color);
void		mlx_put_point(t_img_data *img_data, t_vector point, int color);
void		draw_line(t_img_data *data, t_vector a, t_vector b, int color);
void		draw_rectangle(t_img_data *img_data, t_rectangle rectangle);
void		draw_background(t_cub *cub);
void		draw_sprite(t_cub *cub, t_draw_param dp, const float *z_buffer, float dist);
void		draw_collectible(t_cub *cub, t_collectible collectible, const float *z_buffer);
void		draw_enemy(t_cub *cub, t_enemy enemy, const float *z_buffer);
void		draw_sprites(t_cub *cub, const float *z_buffer);
void		draw_wall(t_cub *cub, int x, t_ray ray);
void		draw_player_view(t_cub *cub);

/* --- DRAW UTILS FUNCTIONS --- */

void			collectible_set_dist(t_cub *cub, t_player player);
void			collectible_sort(t_cub *cub);
void			enemies_set_dist(t_cub *cub, t_enemy *enemies, t_player player);
void			enemies_sort(t_enemy *enemies);
t_draw_param	enemy_get_draw_param(t_cub *cub, t_fvector camera);
t_fvector		enemy_camera_projection(t_cub *cub, t_enemy enemy);

/* --- POINT_UTILS FUNCTIONS --- */

t_rectangle	set_rectangle(t_vector start, t_vector end, int color);
t_rectangle	set_square(t_vector start, int width, int color);
int			is_valid_pixel(t_vector point);

#endif
