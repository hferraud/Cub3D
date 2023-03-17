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

typedef struct s_point		t_point;
typedef struct s_rectangle	t_rectangle;
typedef	struct s_ray		t_ray;

struct s_point
{
	int	x;
	int	y;
};

struct s_rectangle
{
	t_point	start;
	t_point	end;
	int		color;
};

/* --- DRAW FUNCTIONS --- */

void		mlx_put_pixel(t_img_data *img_data, int x, int y, int color);
void		mlx_put_point(t_img_data *img_data, t_point point, int color);
void		draw_line(t_img_data *data, t_point a, t_point b, int color);
void		draw_rectangle(t_img_data *img_data, t_rectangle rectangle);
void		draw_background(t_cub *cub);
void		draw_wall(t_cub *cub, int x, t_ray ray);
void		draw_player_view(t_cub *cub, float fov);
void		draw_minimap(t_cub *cub);

/* --- POINT_UTILS FUNCTIONS --- */

t_point		set_point(int x, int y);
t_rectangle	set_rectangle(t_point start, t_point end, int color);
t_rectangle	set_square(t_point start, int width, int color);
int			is_valid_point(t_point point);

#endif
