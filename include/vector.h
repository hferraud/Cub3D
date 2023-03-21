/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 05:24:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/20 05:24:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vector		t_vector;
typedef struct s_fvector	t_fvector;
typedef struct s_matrix		t_matrix;

struct s_vector
{
	int	x;
	int	y;
};

struct s_fvector
{
	float	x;
	float	y;
};

struct s_matrix
{
	float	m[2][2];
};

t_vector	vector_init(int x, int y);
t_vector	vector_add(t_vector v1, t_vector v2);
t_vector	vector_sub(t_vector v1, t_vector v2);
t_vector	vector_mul(t_vector v, float m);
t_vector	vector_div(t_vector v, float d);
t_fvector	fvector_init(float x, float y);
t_fvector	fvector_add(t_fvector v1, t_fvector v2);
t_fvector	fvector_sub(t_fvector v1, t_fvector v2);
t_fvector	fvector_mul(t_fvector v, float m);
t_fvector	fvector_div(t_fvector v, float d);
t_matrix	matrix_rotation(float theta);
t_fvector	fvector_rotate(t_fvector fvector, float theta);

#endif
