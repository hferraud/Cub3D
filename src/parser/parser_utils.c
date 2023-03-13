/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 03:23:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/13 03:23:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

void	init_map_data(t_map *map)
{
	ft_bzero(&map->wall, sizeof (t_wall));
	map->map = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
}

/**
 * @brief Check if the file extension is .cub
 */
int	is_valid_filename(char *filename)
{
	const size_t	len = ft_strlen(filename);

	return (ft_strcmp(filename + (len - 4), ".cub") == 0);
}

void	clear_map_data(t_map *map)
{
	if (map->wall.wall[NORTH])
		free(map->wall.wall[NORTH]);
	if (map->wall.wall[SOUTH])
		free(map->wall.wall[SOUTH]);
	if (map->wall.wall[EAST])
		free(map->wall.wall[EAST]);
	if (map->wall.wall[WEST])
		free(map->wall.wall[WEST]);
	if (map->map)
		free_string_array(map->map);
}

/**
 * @brief Print the error message, use errno if error_msg is NULL.
 * @return Always return -1
 */
int	parser_error(char *error_msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (error_msg == NULL)
		perror(NULL);
	else
		ft_putstr_fd(error_msg, STDERR_FILENO);
	return (-1);
}
