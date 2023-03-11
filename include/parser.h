/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 05:32:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/11 05:32:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "get_next_line.h"
# include "libft.h"
# include "map.h"


typedef enum	e_map_id_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	UNDEFINED
}				t_map_id_type;

#endif
