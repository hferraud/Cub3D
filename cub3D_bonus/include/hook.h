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
# define ON_KEY_DOWN			2
# define ON_KEY_UP				3

typedef struct s_cub	t_cub;

enum	e_mask
{
	KEY_PRESS_MASK		=	1L << 0,
	KEY_RELEASE_MASK	=	1L << 1,
	BUTTON_RELEASE_MASK	=	1L << 3
};

void	init_hook(t_cub *cub);

/* --- HOOK FUNCTIONS --- */

int		is_key_pressed(int key_code, t_cub *cub);
int		key_press(int key_code, t_cub *cub);
int		key_release(int key_code, t_cub *cub);
int		cub_exit(t_cub *cub);

#endif
