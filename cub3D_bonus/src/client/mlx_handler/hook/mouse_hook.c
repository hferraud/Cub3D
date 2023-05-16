/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 04:08:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/05/16 04:08:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "cub.h"

int	mouse_hook(int button, int x, int y, t_cub *cub)
{
	(void)x;
	(void)y;
	if (cub->mlx_data->mouse_disable)
		return (0);
	if (button == MOUSE_BUTTON_1)
		player_shoot(cub);
	return (0);
}
