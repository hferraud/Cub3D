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
# include "map_client.h"
# include "mlx_handler.h"
# include "player_data.h"
# include "texture.h"

typedef struct s_cub		t_cub;
typedef struct s_map_client	t_map_client;
typedef struct s_mlx_data	t_mlx_data;
typedef struct s_player		t_player;

struct s_cub
{
	int				server_socket;
	t_map_client	map;
	t_mlx_data		*mlx_data;
	t_player_data	player_data;
};

#endif
