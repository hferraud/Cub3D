/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_sprite_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/13 23:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"

static int	error_wall_sprite_init(t_cub *cub);

/**
 * @brief Create mlx_image of walls sprites.
 * If an error occurred an error message is displayed
 * @return 0 on success, -1 otherwise
 */
int	wall_sprite_init(t_cub *cub)
{
	size_t	index;

	index = 0;
	while (index < 4)
	{
		cub->mlx_data.wall[index].img = mlx_xpm_file_to_image(cub->mlx_data.mlx_ptr, cub->map.wall_path[index], &cub->mlx_data.wall[index].width, &cub->mlx_data.wall[index].height);
		free(cub->map.wall_path[index]);
		cub->map.wall_path[index] = NULL;
		if (cub->mlx_data.wall[index].img == NULL)
			return (error_wall_sprite_init(cub));
		index++;
	}
	return (0);
}

static int	error_wall_sprite_init(t_cub *cub)
{
	size_t	index;

	index = 0;
	while (index < 4)
	{
		free(cub->map.wall_path[index]);
		cub->map.wall_path[index] = NULL;
		if (cub->mlx_data.wall[index].img)
			mlx_destroy_image(cub->mlx_data.mlx_ptr, cub->mlx_data.wall[index].img);
		cub->mlx_data.wall[index].img = NULL;
		index++;
	}
	return (cub_error("mlx_xpm_file_to_image() failed\n"));
}