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
# include "collectible.h"

typedef enum e_wall				t_wall;
typedef struct s_ray			t_ray;
typedef struct s_raycast_param	t_raycast_param;

enum e_wall
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
};

struct s_ray
{
	t_fvector			ray;
	t_fvector			pos;
	t_fvector			unit_step;
	t_vector			step;
	t_wall				wall_face;
	bool				is_door;
	float				length;
};

struct s_raycast_param
{
	int		start;
	int		end;
	t_cub	*cub;
};

t_ray	ray_cast(t_cub *cub, t_fvector ray_dir);

#endif
