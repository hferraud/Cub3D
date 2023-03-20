/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 10:16:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/20 10:16:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "vector.h"

t_matrix	matrix_rotation(float theta)
{
	t_matrix	matrix;

	matrix.m[0][0] = cosf(theta);
	matrix.m[0][1] = -sinf(theta);
	matrix.m[1][0] = sinf(theta);
	matrix.m[1][1] = cosf(theta);
	return (matrix);
}

t_fvector	fvector_rotate(t_fvector fvector, float theta)
{
	t_matrix	matrix;

	matrix = matrix_rotation(theta);
	fvector.x = matrix.m[0][0] * fvector.x + matrix.m[0][1] * fvector.y;
	fvector.y = matrix.m[1][0] * fvector.x + matrix.m[1][1] * fvector.y;
	return (fvector);
}
