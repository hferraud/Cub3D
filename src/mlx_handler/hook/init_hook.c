/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:16:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 07:16:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "hook.h"

void	init_hook(t_cub *cub)
{
	mlx_hook(cub->mlx_data.win_ptr, ON_DESTROY, BUTTON_RELEASE_MASK,
		cub_exit, cub);
}