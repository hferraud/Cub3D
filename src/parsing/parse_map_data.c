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
static int				parse_wall(char *line, t_content_type content_type, t_map *map);
static int				parse_horizontal_plane(const char *line, t_content_type map_id, t_map *map);

int	map_data_parser(int map_fd, t_map *map)
{
	char		*line;

	line = get_next_line(map_fd);
	while (line)
	{
		map_data_parse_router(line, map);
		line = get_next_line(map_fd);
	}
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

/**
 * @brief Get the path associated with a wall texture and add it to map struct
 * @return 0 on success, -1 otherwise
 */
static int	parse_wall(char *line, t_content_type content_type, t_map *map)
{
	char	*sprite_path;

	while (*line && *line == ' ')
		line++;
	if (*line == '\0')
		return (parser_error("File name is missing\n"));
	sprite_path = ft_strdup(line);
	if (sprite_path == NULL)
		return (parser_error(NULL));
	if (content_type == NORTH)
		map->wall.sprite_no = sprite_path;
	else if (content_type == SOUTH)
		map->wall.sprite_so = sprite_path;
	else if (content_type == WEST)
		map->wall.sprite_we = sprite_path;
	else if (content_type == EAST)
		map->wall.sprite_ea = sprite_path;
	return (0);
}

static int	parse_horizontal_plane(t_map *map, const char *line, t_content_type map_id)
{

}

