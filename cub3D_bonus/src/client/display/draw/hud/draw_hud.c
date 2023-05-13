/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:02:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/12 13:02:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hud.h"

void	draw_hud(t_cub *cub)
{
	draw_weapon_view(cub);
	draw_minimap(cub);
	draw_health_bar(cub);
	draw_ammo(cub);
	draw_weapon(cub);
	draw_crosshair(cub->mlx_data);
}
