/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 15:29:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/24 15:29:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAP_BONUS_H
# define MAP_BONUS_H

# include <sys/types.h>
# include <stdlib.h>

# define FLOOR			'0'
# define WALL			'1'
# define DOOR_CLOSE		'2'
# define DOOR_OPEN		'3'
# define LIFE_PACK		'L'
# define AMMO			'A'
# define PISTOL			'G'
# define ASSAULT_RIFLE	'R'
# define ENEMY			'P'

typedef struct s_map	t_map;
typedef struct s_spawn	t_spawn;
typedef enum e_wall		t_wall;

struct s_spawn
{
	size_t	x;
	size_t	y;
	char	orientation;
};

enum e_wall
{
	NORTH	=	0,
	SOUTH	=	1,
	EAST	=	2,
	WEST	=	3
};

struct s_map
{
	char	**map;
	size_t	height;
	size_t	width;
	t_spawn	spawn;
	char	*wall_path[4];
	char	*horizontal_plane[2];
};

#endif
