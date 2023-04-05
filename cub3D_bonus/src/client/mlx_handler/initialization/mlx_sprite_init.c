/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_sprite_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/13 23:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"

static int		mlx_texture_sprite_init(t_cub *cub);
static int		mlx_collectible_sprite_init(t_mlx_data *mlx_data);
static t_sprite	mlx_sprite_open(t_mlx_data *mlx_data, char *path);
static int		error_sprite_init(t_cub *cub);

/**
 * @brief Create mlx_image of textures sprites.
 * If an error occurred an error message is displayed
 * @return 0 on success, -1 otherwise
 */
int	mlx_sprite_init(t_cub *cub)
{
	if (mlx_texture_sprite_init(cub) == -1
		|| mlx_collectible_sprite_init(cub->mlx_data) == -1)
		return (error_sprite_init(cub));
	return (0);
}

static int	mlx_texture_sprite_init(t_cub *cub)
{
	t_sprite	*sprite;
	size_t		index;

	index = 0;
	while (index < NB_TEXTURE)
	{
		sprite = &cub->mlx_data->texture_sprite[index];
		*sprite = mlx_sprite_open(cub->mlx_data, cub->map.path[index]);
		free(cub->map.path[index]);
		cub->map.path[index] = NULL;
		if (sprite->img_data.img == NULL)
			return (-1);
		index++;
	}
	return (0);
}

static int	mlx_collectible_sprite_init(t_mlx_data *mlx_data)
{
	const char	*paths[] = {MEDIC_KIT_PATH, AMMO_PATH, PISTOL_PATH,
		ASSAULT_RIFFLE_PATH, NULL};
	t_sprite	*sprite;
	size_t		index;

	index = 0;
	while (index < NB_COLLECTIBLE)
	{
		sprite = &mlx_data->collectible_sprite[index];
		*sprite = mlx_sprite_open(mlx_data, (char *) paths[index]);
		if (sprite->img_data.img == NULL)
			return (-1);
		index++;
		index++;
	}
	return (0);
}

static t_sprite	mlx_sprite_open(t_mlx_data *mlx_data, char *path)
{
	t_sprite	sprite;

	sprite.img_data.img = mlx_xpm_file_to_image(mlx_data->mlx_ptr, path,
			&sprite.width, &sprite.height);
	if (sprite.img_data.img == NULL)
		return (sprite);
	sprite.img_data.addr = mlx_get_data_addr(sprite.img_data.img,
			&sprite.img_data.bits_per_pixel,
			&sprite.img_data.line_length, &sprite.img_data.endian);
	sprite.img_data.bit_ratio = sprite.img_data.bits_per_pixel / 8;
	return (sprite);
}

static int	error_sprite_init(t_cub *cub)
{
	size_t	index;

	index = 0;
	while (index < NB_TEXTURE)
	{
		free(cub->map.path[index]);
		cub->map.path[index] = NULL;
		if (cub->mlx_data->texture_sprite[index].img_data.img)
			mlx_destroy_image(cub->mlx_data->mlx_ptr,
				cub->mlx_data->texture_sprite[index].img_data.img);
		cub->mlx_data->texture_sprite[index].img_data.img = NULL;
		index++;
	}
	index = 0;
	while (index < NB_COLLECTIBLE)
	{
		if (cub->mlx_data->collectible_sprite[index].img_data.img)
			mlx_destroy_image(cub->mlx_data->mlx_ptr,
				cub->mlx_data->collectible_sprite[index].img_data.img);
		cub->mlx_data->collectible_sprite[index].img_data.img = NULL;
		index++;
	}
	return (cub_error("mlx_xpm_file_to_image() failed\n"));
}
