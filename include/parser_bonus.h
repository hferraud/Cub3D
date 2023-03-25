/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 16:01:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/25 16:01:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include "libft.h"
# include "get_next_line.h"
# include "map_bonus.h"
# include "error.h"

# define PLAYER_LIMIT	10

typedef enum e_content_type	t_content_type;

enum e_content_type
{
	NORTH_ID,
	SOUTH_ID,
	WEST_ID,
	EAST_ID,
	FLOOR_ID,
	CEILING_ID,
	DOOR_ID,
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
void	map_data_clear(t_map *map);
int		is_valid_filename(char *filename);
int		parse_path(char *line, t_content_type type, t_map *map);

/* --- PARSER_MAP_UTILS FUNCTIONS --- */

int		is_valid_map_list(t_list *head);
char	*skip_empty_line(int map_fd);
size_t	get_max_row_size(t_list *head);

#endif
