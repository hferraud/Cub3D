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
# include "vector.h"

# define PLAYER_OFFSET		0.2
# define PLAYER_FOV			M_PI_2
# define PLAYER_MOVE		0.025
# define PLAYER_ROTATION	0.025
# define UNCERTAINTY		0.01

typedef struct s_player	t_player;

struct s_player
{
	t_fvector	pos;
	t_fvector	rotation;
};

typedef struct s_cub	t_cub;

void	player_update(t_cub *cub);

#endif
