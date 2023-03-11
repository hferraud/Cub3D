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

static t_map_id_type	map_data_get_id_type(char **line);
static int				map_data_parse_router(const char line,
							t_map_id_type map_id)

int	map_data_parser(int map_fd, t_map *map)
{
    char        	*line;
	t_map_id_type	map_id_type;

    line = get_next_line(map_fd);
    while (line)
    {
		map_id_type = map_data_get_id_type(&line);
		//map_data_parse_router();
        line = get_next_line(map_fd);
    }
}

static int parse_wall_id(char *line)
{

}

static t_map_id_type map_data_get_id_type(char **line)
{
	const char  *map_id[] = {"NO", "SO", "WE", "EA", "F", "C", NULL};
    const t_map_id_type id_type[] = {NORTH, SOUTH, WEST, EAST, FLOOR, CEILING};
	int	    	i;
	int			j;

	i = 0;
	while(map_id[i])
	{
		j = 0;
		while(map_id[i][j] == (*line)[j] && (*line)[j])
			j++;
		if (map_id[i][j] == '\0' && (*line)[j] == ' ')
        {
            *line += j;
            return (id_type[i]);
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
