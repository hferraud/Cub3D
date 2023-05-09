/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 11:22:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 11:22:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hook.h"
#include "draw.h"
#include <sys/time.h>

static void		limit_fps(struct timeval start, struct timeval current, int fps_max);
static size_t	diff_time(struct timeval start_time, struct timeval current_time);

/**
 * @brief Update player params and calculate the next image to display
 */
int	render_frame(t_cub *cub)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	pthread_mutex_lock(cub->client_status.status_lock);
	if (cub->client_status.status == ERROR)
	{
		pthread_mutex_unlock(cub->client_status.status_lock);
		cub_exit(cub);
	}
	pthread_mutex_unlock(cub->client_status.status_lock);
	player_update(cub);
	draw_background(cub);
	draw_player_view(cub);
	mlx_put_image_to_window(cub->mlx_data->mlx_ptr, cub->mlx_data->win_ptr,
		cub->mlx_data->img_data.img, 0, 0);
	gettimeofday(&current, NULL);
	limit_fps(start, current, 60);
	return (0);
}

static void	limit_fps(struct timeval start, struct timeval current, int fps_max)
{
	size_t			delta;
	const size_t	usec_per_frame = 1000000 / fps_max;

	delta = diff_time(start, current);
	if (usec_per_frame > delta)
		usleep(usec_per_frame - delta);
}

static size_t	diff_time(struct timeval start_time, struct timeval current_time)
{
	return ((size_t)(current_time.tv_sec - start_time.tv_sec) * 1000000
			+ (current_time.tv_usec - start_time.tv_usec));
}
