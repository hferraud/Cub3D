/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 13:07:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/06 11:18:18 by hferraud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PLAYER_H
# define PLAYER_H

# include <math.h>
# include "vector.h"

# define PLAYER_OFFSET		0.2f
# define PLAYER_FOV			M_PI_2
# define PLAYER_MOVE		0.1f
# define PLAYER_ROTATION	0.05f
# define UNCERTAINTY		0.001f

typedef struct s_player	t_player;

struct s_player
{
	t_fvector	pos;
	t_fvector	rotation;
};

typedef struct s_cub	t_cub;

void		player_pos_init(t_cub *cub);
void		player_update(t_cub *cub);
t_fvector	new_position_calculate(t_cub *cub);
int			is_valid_position(t_cub *cub, float x, float y);
int			player_moved(t_player before, t_player current);
int			is_floor(char cell);
void		player_door_interact(t_cub *cub);


int			player_hit_collectible(t_cub *cub);
void		player_shoot(t_cub *cub);
void		check_assault_riffle_shoot(t_cub *cub);

#endif
