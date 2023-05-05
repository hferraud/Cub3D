/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 23:00:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/29 23:00:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB_H
# define CUB_H

# include "error.h"
# include "define.h"
# include "map_client.h"
# include "mlx_handler.h"
# include "player_data.h"
# include "texture.h"

typedef struct s_cub			t_cub;
typedef struct s_client_status	t_client_status;
typedef struct s_map_client		t_map_client;
typedef struct s_mlx_data		t_mlx_data;
typedef struct s_player			t_player;
typedef struct s_enemy			t_enemy;

enum e_status
{
	RUNNING,
	ERROR,
};

struct s_client_status
{
	int				status;
	pthread_mutex_t	*status_lock;
};

struct s_enemy
{
	t_player	player;
	int			id;
	t_fvector	relative_pos;
	float		dist;
};

struct s_cub
{
	int				server_socket;
	t_client_status	client_status;
	t_map_client	map;
	t_mlx_data		*mlx_data;
	t_player_data	player_data;
	t_enemy			enemies[PLAYER_LIMIT - 1];
	pthread_mutex_t	*players_lock;
	pthread_t		thread;
};

#endif
