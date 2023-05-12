/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:28:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/09 16:28:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef HUD_H
# define HUD_H

# include "cub.h"

# define BULLET_PATH		"asset/bullet.xpm"
# define KNIFE_HUD_PATH		"asset/knife_hud.xpm"
# define PISTOL_HUD_PATH	"asset/pistol_hud.xpm"
# define AR_HUD_PATH		"asset/assault_rifle_hud.xpm"

# define MAP_HALF_SIZE 5
# define MAP_RADIUS 80
# define MAP_PIXEL_OFFSET 20

# define HEALTH_BAR_WIDTH 300
# define HEALTH_BAR_HEIGHT 39
# define HEALTH_BAR_OFFSET 20
# define BORDER_SIZE 3
# define BORDER_RADIUS 20

# define AMMO_Y_OFFSET 20
# define AMMO_X_OFFSET 240
# define BULLET_PER_ROW 10
# define BULLET_Y_OFFSET 10

# define WEAPON_OFFSET 20
# define WEAPON_WIDTH 220
# define WEAPON_HEIGHT 150


void	draw_hud(t_cub *cub);
void	draw_minimap(t_cub *cub);
void	draw_minimap_pixel(t_cub *cub, t_vector screen, t_fvector map_pos);
void	draw_health_bar(t_cub *cub);
void	draw_ammo(t_cub *cub);
void	draw_weapon(t_cub *cub);

#endif