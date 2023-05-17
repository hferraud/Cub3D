/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_sprite_destroy.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 02:10:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 02:10:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"

static void	mlx_texture_destroy(t_mlx_data *mlx_data);
static void	mlx_collectible_destroy(t_mlx_data *mlx_data);
static void	mlx_hud_destroy(t_mlx_data *mlx_data);
static void	mlx_animation_destroy(t_mlx_data *mlx_data);

void	mlx_sprite_destroy(t_mlx_data *mlx_data)
{
	mlx_texture_destroy(mlx_data);
	mlx_collectible_destroy(mlx_data);
	mlx_hud_destroy(mlx_data);
	destroy_sprite(mlx_data->mlx_ptr, &mlx_data->enemy_sprite);
}

static void	mlx_texture_destroy(t_mlx_data *mlx_data)
{
	size_t	index;

	index = 0;
	while (index < NB_TEXTURE)
	{
		destroy_sprite(mlx_data->mlx_ptr, &mlx_data->texture_sprite[index]);
		index++;
	}
}

static void	mlx_collectible_destroy(t_mlx_data *mlx_data)
{
	size_t	index;

	index = 0;
	while (index < NB_COLLECTIBLE)
	{
		destroy_sprite(mlx_data->mlx_ptr, &mlx_data->collectible_sprite[index]);
		index++;
	}
}

static void	mlx_hud_destroy(t_mlx_data *mlx_data)
{
	size_t	index;

	destroy_sprite(mlx_data->mlx_ptr, &mlx_data->hud_sprite.ammo);
	destroy_sprite(mlx_data->mlx_ptr, &mlx_data->hud_sprite.death_screen);
	index = 0;
	while (index < NB_WEAPONS)
	{
		destroy_sprite(mlx_data->mlx_ptr, &mlx_data->hud_sprite.weapon[index]);
		index++;
	}
	mlx_animation_destroy(mlx_data);
}

static void	mlx_animation_destroy(t_mlx_data *mlx_data)
{
	size_t	index;

	index = 0;
	while (index < NB_KNIFE_SPRITES)
	{
		destroy_sprite(mlx_data->mlx_ptr, &mlx_data->hud_sprite.knife[index]);
		index++;
	}
	index = 0;
	while (index < NB_PISTOL_SPRITES)
	{
		destroy_sprite(mlx_data->mlx_ptr, &mlx_data->hud_sprite.pistol[index]);
		index++;
	}
	index = 0;
	while (index < NB_AR_SPRITES)
	{
		destroy_sprite(mlx_data->mlx_ptr,
			&mlx_data->hud_sprite.assault_rifle[index]);
		index++;
	}
}
