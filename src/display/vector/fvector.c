/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 05:30:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/20 05:30:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "vector.h"

t_fvector	fvector_init(float x, float y)
{
	t_fvector	vect;

	vect.x = x;
	vect.y = y;
	return (vect);
}

t_fvector	fvector_add(t_fvector v1, t_fvector v2)
{
	return (fvector_init(v1.x + v2.x, v1.y + v2.y));
}

t_fvector	fvector_sub(t_fvector v1, t_fvector v2)
{
	return (fvector_init(v1.x - v2.x, v1.y - v2.y));
}

t_fvector	ffvector_mult(t_fvector v, float m)
{
	return (fvector_init(v.x * m, v.y * m));
}

t_fvector	fvector_div(t_fvector v, float d)
{
	return (fvector_init(v.x / d, v.y / d));
}
