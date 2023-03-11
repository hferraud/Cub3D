/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:42:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/09 19:42:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	open_mapfile(char *filename);
static int	parser_error(void);

int	parser(int argc, char **argv, t_map *map)
{
	int		map_fd;

	if (argc != 2)
		return (parser_error());
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd == -1)
		return (parser_error());
	close(map_fd);
}

static int	parse_map_data(int map_fd, t_map *map)
{
	const char *wall_id[4] = {"NO", "SO", "WE", "EA"};
	const char *wall_
	const char *floor_id = "F";
	const char *ceiling_id = "C";
}

static int	parser_error(void)
{
	write(2, "Error\n", 6);
	return (-1);
}
