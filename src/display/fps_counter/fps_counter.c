/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 05:30:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/22 05:30:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <sys/time.h>

static int	timestamp_get(struct timeval time_last_frame,
							struct timeval current_time);
double		fps_average(int fps, int get_average);

void	fps_count()
{
	static struct timeval	time_last_frame;
	struct timeval			current_time;
	int						fps;

	gettimeofday(&current_time, NULL);
	if (time_last_frame.tv_sec != 0 || time_last_frame.tv_usec != 0)
	{
		fps = 1000000 / timestamp_get(time_last_frame, current_time);
		ft_putstr("fps: ");
		ft_putnbr(fps);
		ft_putchar('\n');
		fps_average(fps, 0);
	}
	time_last_frame = current_time;
}

double fps_average(int fps, int get_average)
{
	static size_t	nb_frame;
	static size_t	total_fps;

	if (get_average)
		return ((double) total_fps / (double) nb_frame);
	else
	{
		total_fps += fps;
		nb_frame++;
	}
	return (0);
}

static int	timestamp_get(struct timeval time_last_frame,
							struct timeval current_time)
{
	return ((current_time.tv_sec - time_last_frame.tv_sec) * 1000000
		+ current_time.tv_usec - time_last_frame.tv_usec);
}