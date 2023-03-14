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

# include "libft.h"
# include "mlx.h"
# include "map.h"
# include "error.h"
# include <stdio.h>

# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define WIN_NAME	"Cub3D"

# define MAX_KEY	6

/* --- TYPEDEF --- */

typedef struct s_cub		t_cub;
typedef struct s_mlx_data	t_mlx_data;
typedef struct s_sprite		t_sprite;
typedef struct s_img_data	t_img_data;

/* --- FUNCTIONS --- */

int		mlx_data_init(t_cub *cub);
void	mlx_data_destroy(t_mlx_data *mlx_data);
int		wall_sprite_init(t_cub *cub);
void	wall_sprite_destroy(t_mlx_data *mlx_data);

/* --- STRUCT --- */

struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_sprite
{
	void	*img;
	int		width;
	int		height;
};

struct s_mlx_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img_data	img_data;
	t_sprite	wall[4];
	int			key_press[MAX_KEY];
};

struct s_cub
{
	t_mlx_data	mlx_data;
	t_map		map;
};

#endif
