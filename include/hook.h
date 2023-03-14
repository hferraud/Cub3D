/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 07:35:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 07:35:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef HOOK_H
# define HOOK_H

# include "mlx_handler.h"
# include "mlx_key.h"

# define ON_DESTROY				17
# define BUTTON_RELEASE_MASK	1L << 3

void	init_hook(t_cub *cub);
int		cub_exit(t_cub* cub);

#endif
