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

# define MAP_SIZE 10
# define MAP_HALF_SIZE 5
# define MAP_DIAMETER 160
# define MAP_RADIUS 80
# define MAP_PIXEL_OFFSET 10

void	draw_minimap(t_cub *cub);
void	draw_minimap_pixel(t_cub *cub, t_vector screen, t_fvector map_pos);

#endif