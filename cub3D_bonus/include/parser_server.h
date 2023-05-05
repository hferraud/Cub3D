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
#ifndef PARSER_SERVER_H
# define PARSER_SERVER_H

# include <sys/types.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <limits.h>
# include <stdbool.h>
# include "libft.h"
# include "get_next_line.h"
# include "map_server.h"
# include "error.h"
# include "define.h"

/* --- PARSER FUNCTION --- */

int		parser(char **argv, t_map *map);
int		parse_map_data(int map_fd, t_map *map);
int		parse_map(int map_fd, t_map *map);

/* --- CHECKER MAP FUNCTION --- */

int		get_spawn_position(t_map *map);
int		is_valid_map(char **map);
void	map_error(size_t line, size_t column);

/* --- PARSER_UTILS FUNCTIONS --- */

void	init_map_data(t_map *map);
void	map_data_clear(t_map *map);
int		is_valid_filename(char *filename);
int		parse_path(char *line, t_texture_id type, t_map *map);

/* --- PARSER_MAP_UTILS FUNCTIONS --- */

int		is_valid_map_list(t_list *head);
char	*skip_empty_line(int map_fd);
size_t	get_max_row_size(t_list *head);

#endif
