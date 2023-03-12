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

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <limits.h>
# include "get_next_line.h"
# include "libft.h"
# include "map.h"

typedef enum e_content_type
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING,
	UNDEFINED
}				t_content_type;

int	parser(int argc, char **argv, t_map *map);
int	parse_map_data(int map_fd, t_map *map);
int	parse_wall(char *line, t_content_type content_type, t_map *map);
int	parse_horizontal_plane(char *line, t_content_type type, t_map *map);
int	parser_error(char *error_msg);

#endif
