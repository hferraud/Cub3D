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
# define MAP_PIXEL_SIZE 150
# define MAP_PIXEL_HALF_SIZE 75
# define CELL_PIXEL_SIZE 15
# define MAP_PIXEL_OFFSET 10

void	draw_minimap(t_cub *cub);

#endif