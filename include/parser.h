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
# include <stdbool.h>
# include "get_next_line.h"
# include "libft.h"
# include "map.h"
# include "error.h"

typedef enum e_content_type t_content_type;

enum e_content_type
{
	NORTH_ID,
	SOUTH_ID,
	WEST_ID,
	EAST_ID,
	FLOOR_ID,
	CEILING_ID,
	UNDEFINED_ID
};

/* --- PARSER FUNCTION --- */

int		parser(int argc, char **argv, t_map *map);
int		parse_map_data(int map_fd, t_map *map);
int		parse_map(int map_fd, t_map *map);

/* --- CHECKER MAP FUNCTION --- */

int		get_spawn_position(t_map *map);
int		is_valid_map(char **map);

/* --- PARSER_UTILS FUNCTIONS --- */

void	init_map_data(t_map *map);
void	clear_map_data(t_map *map);
int		is_valid_filename(char *filename);
int		parse_wall(char *line, t_content_type content_type, t_map *map);
int		parse_horizontal_plane(char *line, t_content_type type, t_map *map);

/* --- PARSER_MAP_UTILS FUNCTIONS --- */

int		is_valid_map_list(t_list *head);
char	*skip_empty_line(int map_fd);
size_t	get_max_row_size(t_list *head);

#endif
