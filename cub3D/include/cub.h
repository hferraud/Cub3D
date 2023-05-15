/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 03:51:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/15 03:51:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB_H
# define CUB_H

# include "parser.h"
# include "mlx_handler.h"
# include "player.h"

typedef struct s_cub		t_cub;
typedef struct s_mlx_data	t_mlx_data;
typedef struct s_map		t_map;
typedef struct s_player		t_player;

struct s_cub
{
	t_mlx_data	*mlx_data;
	t_map		*map;
	t_player	*player;
};

#endif
