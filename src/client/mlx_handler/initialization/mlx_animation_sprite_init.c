/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_animation_sprite_init.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:25:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/12 16:25:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"
#include "hud.h"

static int	mlx_knife_sprite_init(t_mlx_data *mlx_data);
static int	mlx_pistol_sprite_init(t_mlx_data *mlx_data);
static int	mlx_ar_sprite_init(t_mlx_data *mlx_data);

int	mlx_animation_sprite_init(t_mlx_data *mlx_data)
{
	if (mlx_knife_sprite_init(mlx_data) == -1
		|| mlx_pistol_sprite_init(mlx_data) == -1
		|| mlx_ar_sprite_init(mlx_data) == -1)
		return (-1);
	return (0);
}

static int	mlx_pistol_sprite_init(t_mlx_data *mlx_data)
{
	const char		*pistol_path[] = {PISTOL_0, PISTOL_1, PISTOL_2,
		PISTOL_3, PISTOL_4, PISTOL_5, PISTOL_6, PISTOL_7};
	t_hud_sprite	*hud_sprite;
	size_t			index;

	index = 0;
	hud_sprite = &mlx_data->hud_sprite;
	while (index < NB_PISTOL_SPRITES)
	{
		hud_sprite->pistol[index]
			= mlx_sprite_open(mlx_data, (char *) pistol_path[index]);
		if (hud_sprite->pistol[index].img_data.img == NULL)
			return (-1);
		index++;
	}
	return (0);
}

static int	mlx_knife_sprite_init(t_mlx_data *mlx_data)
{
	const char		*knife_path[] = {KNIFE_0, KNIFE_1, KNIFE_2,
		KNIFE_3, KNIFE_4, KNIFE_5, KNIFE_6};
	t_hud_sprite	*hud_sprite;
	size_t			index;

	index = 0;
	hud_sprite = &mlx_data->hud_sprite;
	while (index < NB_KNIFE_SPRITES)
	{
		hud_sprite->knife[index]
			= mlx_sprite_open(mlx_data, (char *) knife_path[index]);
		if (hud_sprite->knife[index].img_data.img == NULL)
			return (-1);
		index++;
	}
	return (0);
}

static int	mlx_ar_sprite_init(t_mlx_data *mlx_data)
{
	const char		*ar_path[] = {AR_0, AR_1, AR_2, AR_3, AR_4};
	t_hud_sprite	*hud_sprite;
	size_t			index;

	index = 0;
	hud_sprite = &mlx_data->hud_sprite;
	while (index < NB_AR_SPRITES)
	{
		hud_sprite->assault_rifle[index]
			= mlx_sprite_open(mlx_data, (char *) ar_path[index]);
		if (hud_sprite->assault_rifle[index].img_data.img == NULL)
			return (-1);
		index++;
	}
	return (0);
}
