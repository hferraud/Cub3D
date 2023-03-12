/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_horizontal_plane.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 03:32:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/12 03:32:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int				get_rgb(char *line, int *index);
static unsigned char	iatoc(char *str, int *index);

int	parse_horizontal_plane(char *line, t_content_type type, t_map *map)
{
	int	rgb;
	int	index;

	index = 0;
	while (*line == ' ')
		line++;
	rgb = get_rgb(line, &index);
	if (line[index] != '\n')
		return (parser_error("Format is invalid\n"));
	if (type == FLOOR)
	{
		if (map->floor_color != -1)
			return (parser_error("Duplicate entry detected"));
		map->floor_color = rgb;
	}
	else
	{
		if (map->ceiling_color != -1)
			return (parser_error("Duplicate entry detected"));
		map->ceiling_color = rgb;
	}
	return (0);
}

/**
 * @brief Get the rbg from the .cub file
 * @return -1 if a parsing error occurred, rgb otherwise
 */
static int	get_rgb(char *line, int *index)
{
	int		rgb;
	int		color;
	int		i;

	rgb = 0;
	i = 2;
	while (i >= 0)
	{
		color = iatoc(line, index);
		if (line[*index] != ',' && i != 0)
			return (-1);
		rgb |= (color << (8 * i));
		if (i != 0)
			(*index)++;
		i--;
	}
	return (rgb);
}

/**
 * Convert ascii to char
 * @return Return the char associated, -1 if an error occurred and set the errno
 */
static unsigned char	iatoc(char *str, int *index)
{
	unsigned char	result;

	result = 0;
	while (str[*index] && ft_isdigit(str[*index]))
	{
		if ((result * 10 + (str[*index] - '0')) / 10 != result)
		{
			errno = EOVERFLOW;
			return (-1);
		}
		result = result * 10 + (str[*index] - '0');
		(*index)++;
	}
	return (result);
}