/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:23:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/13 23:23:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef MLX_HANDLER_H
# define MLX_HANDLER_H

# include "mlx.h"
# include "libft.h"
# include "error.h"
# include "cub.h"
# include "texture.h"
# include "collectible.h"
# include "hook.h"
# include <stdio.h>

# define WIN_WIDTH	1280
# define WIN_HEIGHT	720
# define WIN_NAME	"Cub3D"

/* Key hook: w, a, s, d, right, left */
# define MAX_KEY	7

/* --- TYPEDEF --- */

typedef struct s_cub		t_cub;
typedef struct s_mlx_data	t_mlx_data;
typedef struct s_sprite		t_sprite;
typedef struct s_hud_sprite	t_hud_sprite;
typedef struct s_img_data	t_img_data;

/* --- FUNCTIONS --- */

int		mlx_data_init(t_cub *cub);
void	mlx_data_destroy(t_mlx_data *mlx_data);
int		mlx_sprite_init(t_cub *cub);
void	mlx_sprite_destroy(t_mlx_data *mlx_data);

/* --- STRUCT --- */

struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		bit_ratio;
	int		line_length;
	int		endian;
};

struct s_sprite
{
	t_img_data	img_data;
	int			width;
	int			height;
};

struct s_hud_sprite
{
	t_sprite	ammo;
};

struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img_data		img_data;
	t_sprite		texture_sprite[NB_TEXTURE];
	t_sprite		collectible_sprite[NB_COLLECTIBLE];
	t_hud_sprite	hud_sprite;
	int				key_press[MAX_KEY];
};

#endif
