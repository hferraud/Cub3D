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
# include "vector.h"

# define PLAYER_OFFSET		0.2
# define PLAYER_FOV			M_PI_2
# define PLAYER_MOVE		0.1f
# define PLAYER_ROTATION	0.03f
# define UNCERTAINTY		0.001f

typedef struct s_player	t_player;

struct s_player
{
	t_fvector	pos;
	t_fvector	rotation;
};

typedef struct s_cub	t_cub;

void		player_update(t_cub *cub);
t_fvector	new_position_calculate(t_cub *cub);
int			is_valid_position(t_cub *cub, float x, float y);
int			player_moved(t_player before, t_player current);


int			player_hit_collectible(t_cub *cub);
void		add_event_take_collectible(t_cub *cub);

#endif
