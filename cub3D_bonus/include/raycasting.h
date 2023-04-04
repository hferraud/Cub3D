/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 07:31:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/15 07:31:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef RAYCASTING_H
# define RAYCASTING_H

# include <math.h>
# include <stdbool.h>
# include "cub.h"
# include "draw.h"
# include "vector.h"

typedef struct s_ray	t_ray;
typedef struct s_point	t_point;
typedef enum e_wall		t_wall;

enum e_wall
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

struct s_ray
{
	t_fvector	ray;
	t_fvector	pos;
	t_fvector	unit_step;
	t_vector 	step;
    t_wall		wall_face;
	float		length;
};

t_ray   ray_cast(t_cub *cub, t_fvector ray_dir);

#endif
