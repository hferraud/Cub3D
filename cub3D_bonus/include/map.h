/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:29:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/24 15:29:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAP_H
# define MAP_H

# include <sys/types.h>
# include <stdlib.h>
# include "cub.h"
# include "libft.h"

# define FLOOR			'0'
# define WALL			'1'
# define DOOR_CLOSE		'2'
# define DOOR_OPEN		'3'
# define LIFE_PACK		'L'
# define AMMO			'A'
# define PISTOL			'G'
# define ASSAULT_RIFLE	'R'
# define ENEMY			'P'

typedef struct s_map		t_map;
typedef struct s_spawn		t_spawn;

struct s_spawn
{
	size_t	x;
	size_t	y;
	char	orientation;
	int		player_id;
};

struct s_map
{
	char	**map;
	size_t	height;
	size_t	width;
	t_list	*spawn;
	int		nb_spawn;
	char	*path[7];
};

#endif
