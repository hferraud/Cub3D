/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:16:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/03/11 20:16:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static t_content_type	get_content_type(const char *line);
static int				map_data_parse_router(char *line, t_map *map);

int	parse_map_data(int map_fd, t_map *map)
{
	char		*line;

	line = get_next_line(map_fd);
	while (line)
	{
		if (*line != '\n')
			if (map_data_parse_router(line, map) == -1)
				return (-1);
			//TODO map_clear(map);
		line = get_next_line(map_fd);
	}
	return (0);
}

static int	map_data_parse_router(char *line, t_map *map)
{
	t_content_type	content_type;

	content_type = get_content_type(line);
	if (content_type == FLOOR || content_type == CEILING)
		return (parse_horizontal_plane(line + 1, content_type, map));
	else
		return (parse_wall(line + 2, content_type, map));
}

static t_content_type	get_content_type(const char *line)
{
	int						i;
	int						j;
	const char				*content_id[] = {"NO", "SO", "WE", "EA", "F", "C"};
	const t_content_type	content_type[]
		= {NORTH, SOUTH, WEST, EAST, FLOOR, CEILING};

	i = 0;
	while (content_id[i])
	{
		j = 0;
		while (content_id[i][j] == line[j] && line[j])
			j++;
		if (content_id[i][j] == '\0' && line[j] == ' ')
			return (content_type[i]);
		i++;
	}
	return (UNDEFINED);
}
