/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 05:06:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/15 05:06:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "draw.h"

static void	draw_line_x(t_img_data *img_data, t_vector a, t_vector b, int color);
static void	draw_line_y(t_img_data *img_data, t_vector a, t_vector b, int color);
static void	swap_point(t_vector *a, t_vector *b);
static int	approximation(double a);

void	draw_line(t_img_data *data, t_vector a, t_vector b, int color)
{
	if (abs(a.x - b.x) >= abs(a.y - b.y))
		draw_line_x(data, a, b, color);
	else
		draw_line_y(data, a, b, color);
	mlx_put_point(data, b, color);
}

static void	draw_line_x(t_img_data *img_data, t_vector a, t_vector b, int color)
{
	double	coef;
	double	f_zero;

	coef = (double)(a.y - b.y) / (a.x - b.x);
	f_zero = a.y - (coef * a.x);
	if (a.x > b.x)
		swap_point(&a, &b);
	while (a.x != b.x)
	{
		a.y = approximation(a.x * coef + f_zero);
		mlx_put_point(img_data, a, color);
		a.x++;
	}
}

static void	draw_line_y(t_img_data *img_data, t_vector a, t_vector b, int color)
{
	double	coef;
	double	f_zero;

	coef = (double)(a.x - b.x) / (a.y - b.y);
	f_zero = a.x - (coef * a.y);
	if (a.y > b.y)
		swap_point(&a, &b);
	mlx_put_point(img_data, a, color);
	while (a.y != b.y)
	{
		a.x = approximation(a.y * coef + f_zero);
		mlx_put_point(img_data, a, color);
		a.y++;
	}
}

static int	approximation(double a)
{
	int	under_int;

	under_int = (int) a;
	if (a - under_int >= 0.5)
		return (under_int + 1);
	return (under_int);
}

static void	swap_point(t_vector *a, t_vector *b)
{
	t_vector	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
