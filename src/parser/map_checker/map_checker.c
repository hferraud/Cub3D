/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 02:02:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/13 02:02:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	is_valid_extremum(char *line);
static int	is_valid_line(char **map, size_t line);
static int	is_valid_cell(char c);
static void	map_error(size_t line, size_t column);

/**
 * @brief Check if the map is surrounded by walls.
 * If an error occurred, an error message is display.
 * @return 1 on success, 0 otherwise
 */
int	is_valid_map(char **map)
{
	size_t	index;

	if (!is_valid_extremum(map[0]) || map[1] == NULL)
		return (0);
	index = 1;
	while (map[index + 1])
	{
		if (!is_valid_line(map, index))
			return (0);
		index++;
	}
	if (!is_valid_extremum(map[index]))
		return (0);
	return (1);
}

static int	is_valid_line(char **map, size_t line)
{
	size_t	column;

	if (map[line][0] == FLOOR)
		return (0);
	column = 1;
	while (map[line][column])
	{
		if (map[line][column] == FLOOR
			&& (!is_valid_cell(map[line][column -1])
				|| !is_valid_cell(map[line][column + 1])
				|| !is_valid_cell(map[line - 1][column])
				|| !is_valid_cell(map[line + 1][column])))
			return (map_error(line, column), 0);
		column++;
	}
	return (1);
}

static int	is_valid_extremum(char *line)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		if (line[index] == FLOOR)
			return (map_error(0, index), 0);
		index++;
	}
	return (1);
}

static int	is_valid_cell(char c)
{
	return (c == FLOOR || c == WALL);
}

static void	map_error(size_t line, size_t column)
{
	ft_putstr_fd("Error\nMap error at ", STDERR_FILENO);
	ft_putsize_t_fd(line, STDERR_FILENO);
	ft_putstr_fd(", ", STDERR_FILENO);
	ft_putsize_t_fd(column, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
