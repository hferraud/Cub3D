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

typedef struct s_ray	t_ray;
typedef struct s_point	t_point;

struct s_ray
{
	t_pos	ray_pos;
	t_pos	ray_unit_step;
	t_pos	ray_chunk_length;
	t_point	step;
	t_wall	wall_face;
	float	ray_length;
};

t_ray	ray_cast(t_cub *cub, float theta);

#endif
