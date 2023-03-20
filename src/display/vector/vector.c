/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 08:01:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/19 08:01:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "vector.h"

t_vector	vector_init(int x, int y)
{
	t_vector	vect;

	vect.x = x;
	vect.y = y;
	return (vect);
}

t_vector	vector_add(t_vector v1, t_vector v2)
{
	return (vector_init(v1.x + v2.x, v1.y + v2.y));
}

t_vector	vector_sub(t_vector v1, t_vector v2)
{
	return (vector_init(v1.x - v2.x, v1.y - v2.y));
}

t_vector	vector_mult(t_vector v, float m)
{
	return (vector_init(v.x * m, v.y * m));
}

t_vector	vector_div(t_vector v, float d)
{
	return (vector_init(v.x / d, v.y / d));
}
