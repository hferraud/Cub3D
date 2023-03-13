/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 04:16:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/11 04:16:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAP_H
# define MAP_H

# include <sys/types.h>
# include <stdlib.h>

typedef struct s_map	t_map;
typedef struct s_spawn	t_spawn;
typedef struct s_wall	t_wall;

struct s_spawn
{
	size_t	x;
	size_t	y;
	char	orientation;
};

enum e_wall
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

struct s_wall
{
	void	*wall[4];
};

struct s_map
{
	char	**map;
	t_spawn	spawn;
	t_wall	wall;
	int		floor_color;
	int		ceiling_color;
};

# define FLOOR	'0'
# define WALL	'1'

#endif
