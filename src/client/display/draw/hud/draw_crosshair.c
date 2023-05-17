/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_crosshair.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 15:21:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/13 15:21:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hud.h"
#include "draw.h"

static int	get_crosshair_color(t_player_data *player_data);
static void	draw(t_mlx_data *mlx_data, int color);

void	draw_crosshair(t_cub *cub)
{
	t_mlx_data	*mlx_data;
	int			color;

	color = get_crosshair_color(&cub->player_data);
	mlx_data = cub->mlx_data;
	draw(mlx_data, color);
}

static int	get_crosshair_color(t_player_data *player_data)
{
	int	color;

	pthread_mutex_lock(player_data->player_lock);
	if (player_data->player_status.last_shot_hit)
		color = 0xFF0000;
	else
		color = 0xFF00;
	pthread_mutex_unlock(player_data->player_lock);
	return (color);
}

static void	draw(t_mlx_data *mlx_data, int color)
{
	t_vector	start;
	t_vector	end;
	t_vector	middle_screen;

	middle_screen = vector_init(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	start = vector_init(middle_screen.x - 1, middle_screen.y - 1);
	end = vector_init(middle_screen.x, middle_screen.y);
	draw_rectangle(&mlx_data->img_data, set_rectangle(start, end, color));
	start.y = middle_screen.y - 14;
	end.y = middle_screen.y - 6;
	draw_rectangle(&mlx_data->img_data, set_rectangle(start, end, color));
	start.y = middle_screen.y + 5;
	end.y = middle_screen.y + 13;
	draw_rectangle(&mlx_data->img_data, set_rectangle(start, end, color));
	start.y = middle_screen.y - 1;
	start.x = middle_screen.x - 14;
	end.y = middle_screen.y;
	end.x = middle_screen.x - 6;
	draw_rectangle(&mlx_data->img_data, set_rectangle(start, end, color));
	start.x = middle_screen.x + 5;
	end.x = middle_screen.x + 13;
	draw_rectangle(&mlx_data->img_data, set_rectangle(start, end, color));
}
