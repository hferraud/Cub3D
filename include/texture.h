/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:40:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/02 16:40:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef TEXTURE_H
# define TEXTURE_H

# define NB_TEXTURE	7

typedef enum e_texture_id	t_texture_id;

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
