/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:36:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/02 16:36:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAP_CLIENT_H
# define MAP_CLIENT_H

# include <sys/types.h>
# include <stdlib.h>
# include "libft.h"

# define FLOOR			'0'
# define WALL			'1'
# define DOOR_CLOSE		'C'
# define DOOR_OPEN		'O'
# define MEDIC_KIT		'L'
# define AMMO			'A'
# define PISTOL			'G'
# define ASSAULT_RIFLE	'R'
# define ENEMY			'P'

# define DIR_SPRITE		"asset/"

typedef struct s_map_client	t_map_client;
typedef struct s_spawn		t_spawn;

struct s_spawn
{
	size_t	x;
	size_t	y;
	char	orientation;
};

struct s_map_client
{
	char	**map;
	size_t	height;
	size_t	width;
	t_spawn	spawn;
	char	*path[7];
};

void	map_clear(t_map_client *map);

#endif
