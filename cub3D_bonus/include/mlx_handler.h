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

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080

# define ENEMY_PATH	"asset/soldier.xpm"

# include "mlx.h"
# include "libft.h"
# include "error.h"
# include "cub.h"
# include "texture.h"
# include "collectible.h"
# include "hook.h"
# include "weapons_data.h"
# include "hud.h"
# include <stdio.h>
# include <stdbool.h>

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

int			mlx_data_init(t_cub *cub);
void		mlx_data_destroy(t_mlx_data *mlx_data);
int			mlx_sprite_init(t_cub *cub);
void		mlx_sprite_destroy(t_mlx_data *mlx_data);

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
	t_sprite	death_screen;
	t_sprite	weapon[NB_WEAPONS];
	t_sprite	knife[NB_KNIFE_SPRITES];
	t_sprite	pistol[NB_PISTOL_SPRITES];
	t_sprite	assault_rifle[NB_AR_SPRITES];
};

struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img_data		img_data;
	t_sprite		texture_sprite[NB_TEXTURE];
	t_sprite		collectible_sprite[NB_COLLECTIBLE];
	t_sprite		enemy_sprite;
	t_hud_sprite	hud_sprite;
	int				key_press[MAX_KEY];
	bool			mouse_disable;
};

int			mlx_animation_sprite_init(t_mlx_data *mlx_data);
t_sprite	mlx_sprite_open(t_mlx_data *mlx_data, char *path);
void		destroy_sprite(void *mlx_ptr, t_sprite *sprite);
int			error_sprite_init(t_cub *cub);

#endif
