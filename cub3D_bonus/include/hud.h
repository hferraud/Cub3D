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

# define BULLET_PATH	"asset/bullet.xpm"

# define MAP_HALF_SIZE 5
# define MAP_RADIUS 80
# define MAP_PIXEL_OFFSET 20

# define HEALTH_BAR_WIDTH 300
# define HEALTH_BAR_HEIGHT 40
# define HEALTH_BAR_OFFSET 20
# define BORDER_SIZE 3
# define BORDER_RADIUS 20

# define BULLET_PER_ROW 10
# define AMMO_OFFSET 20
# define BULLET_Y_OFFSET 10

void	draw_minimap(t_cub *cub);
void	draw_minimap_pixel(t_cub *cub, t_vector screen, t_fvector map_pos);
void	draw_health_bar(t_cub *cub);
void	draw_ammo(t_cub *cub);

#endif