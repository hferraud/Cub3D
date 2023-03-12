/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 06:33:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/03/12 06:33:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static bool	is_valid_map_row(char *row);

int	parse_map(int map_fd, t_map *map)
{
}

static int	map_to_list(int map_fd, t_list **map_list)
{
	t_list	*elem;
	char	*line;

	line = get_next_line(map_fd);
	while (line && *line == '\n')
		line = get_next_line(map_fd);
	if (line == NULL)
		return (parser_error("Map input is missing\n"));
	map_list = NULL;
	while (line)
	{
		if (is_valid_map_row(line) == false)
			return (parser_error("Format is invalid\n"));
		elem = ft_lstnew(line);
		if (elem == NULL)
			return (parser_error(NULL));
		ft_lstadd_front(map_list, elem);
		line = get_next_line(map_fd);
	}
	ft_lstrev(&map_list);
}

/**
 * @brief check if every character in row is in charset
 */
static bool	is_valid_map_row(char *row)
{
	const char	charset[] = {'1', '0', 'N', 'S', 'W', 'E'};
	bool		flag;
	int			i;

	while (*row)
	{
		flag = false;
		while (!flag && charset[i])
		{
			if (charset[i] == *row)
				flag = true;
			i++;
		}
		if (flag == false)
			return (false);
		row++;
	}
	return (true);
}
