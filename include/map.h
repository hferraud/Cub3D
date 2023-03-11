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

typedef struct s_map	t_map;
typedef struct s_pos	t_pos;
typedef struct s_wall	t_wall;


struct s_pos
{
	unsigned int	x;
	unsigned int	y;
};

struct s_wall
{
	void	*sprite_no;
	void	*sprite_so;
	void	*sprite_we;
	void	*sprite_ea;
};

struct s_map
{
	char	**map;
	t_pos	spawn;
	t_wall	wall;
	int		floor_color;
	int		ceiling_color;
};

#endif
