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
# include "map_server.h"
# include "error.h"

typedef enum e_texture_id	t_texture_id;
typedef struct s_cub		t_cub;
typedef struct s_map		t_map;

enum e_texture_id
{
	NORTH_ID		=	0,
	SOUTH_ID		=	1,
	WEST_ID			=	2,
	EAST_ID			=	3,
	DOOR_ID			=	4,
	FLOOR_ID		=	5,
	CEILING_ID		=	6,
	UNDEFINED_ID	=	7
};

#endif
