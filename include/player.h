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

# include "mlx_handler.h"

# define PLAYER_OFFSET	0.1
# define PLAYER_MOVE	0.05

typedef struct s_player	t_player;

struct s_player
{
	float	x;
	float	y;
	float	rotation;
};

typedef struct s_cub	t_cub;

void	player_position_update(t_cub *cub);

#endif
