/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:07:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/14 13:07:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PLAYER_H
# define PLAYER_H

# include <math.h>
# include "cub.h"

# define PLAYER_OFFSET		0.2
# define PLAYER_FOV			M_PI_2
# define PLAYER_MOVE		0.025
# define PLAYER_ROTATION	0.025
# define UNCERTAINTY		0.01

typedef struct s_player	t_player;
typedef struct s_pos	t_pos;

struct s_pos
{
	float	x;
	float	y;
};

struct s_player
{
	t_pos	pos;
	float	rotation;
};

typedef struct s_cub	t_cub;

void	player_update(t_cub *cub);
t_pos	set_pos(float x, float y);

#endif
