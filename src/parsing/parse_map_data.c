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

static t_map_id_type	map_data_get_id_type(const char *line);
static int				map_data_parse_router(const char line,
							t_map_id_type map_id)

int	map_data_parser(int map_fd, t_map *map)
{
    char        	*line;
	t_map_id_type	map_id_type;

    line = get_next_line(map_fd);
    while (line)
    {
		map_id_type = map_data_get_id_type(line);
		map_data_parse_router();
        line = get_next_line(map_fd);
    }
}

static t_map

static t_map_id_type map_data_get_id_type(const char *line)
{
	const char  *map_id[7] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
	int			i;
	int			j;

	i = 0;
	while(map_id[i])
	{
		j = 0;
		while(map_id[i][j] == line[j] && line[j])
			j++;
		if (map_id[i][j] == '\0' && line[j] == ' ')
		{
			if (i == 0)
				return (NORTH);
			if (i == 1)
				return (SOUTH);
			if (i == 2)
				return (WEST);
			if (i == 3)
				return (EAST);
			if (i == 4)
				return (FLOOR);
			if (i == 5)
				return (CEILING);
		}
		i++;
	}
	return (UNDEFINED);
}

static int map_data_parse_router(const char line, t_map_id_type map_id)
{
	if (map_id == FLOOR || map_id == CEILING)
	{

	}
}
