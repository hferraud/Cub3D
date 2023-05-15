/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 23:39:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/13 23:39:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "mlx_handler.h"

static void	mlx_data_preset(t_mlx_data *mlx_data);
static int	init_img_data(t_mlx_data *mlx_data);

/**
 * @brief Init mlx_data.
 * If an error occurred an error message is displayed
 * @return 0 on success, -1 otherwise
 */
int	mlx_data_init(t_cub *cub)
{
	t_mlx_data	*mlx_data;

	mlx_data = cub->mlx_data;
	mlx_data_preset(mlx_data);
	mlx_data->mlx_ptr = mlx_init();
	if (mlx_data->mlx_ptr == NULL)
		return (cub_error("mlx_init() failed\n"));
	if (mlx_sprite_init(cub) == -1)
		return (mlx_data_destroy(mlx_data), -1);
	mlx_data->win_ptr = mlx_new_window(mlx_data->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, WIN_NAME);
	if (mlx_data->win_ptr == NULL)
		return (mlx_data_destroy(mlx_data),
			cub_error("mlx_new_window() failed\n"));
	if (init_img_data(mlx_data) == -1)
		return (mlx_data_destroy(mlx_data),
			cub_error("mlx_new_image() failed\n"));
	init_hook(cub);
	return (0);
}

/**
 * @brief Init img_data.
 * If an error occurred an error message is displayed
 * @return 0 on success, -1 otherwise
 */
static int	init_img_data(t_mlx_data *mlx_data)
{
	t_img_data	*img_data;

	img_data = &mlx_data->img_data;
	img_data->img = mlx_new_image(mlx_data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (img_data->img == NULL)
		return (cub_error("mlx_new_image() failed\n"));
	img_data->addr = mlx_get_data_addr(img_data->img, &img_data->bits_per_pixel,
			&img_data->line_length, &img_data->endian);
	img_data->bit_ratio = img_data->bits_per_pixel / 8;
	return (0);
}

static void	mlx_data_preset(t_mlx_data *mlx_data)
{
	size_t	index;

	mlx_data->mlx_ptr = NULL;
	mlx_data->win_ptr = NULL;
	mlx_data->img_data.img = NULL;
	ft_bzero(&mlx_data->texture_sprite, sizeof(t_sprite) * NB_TEXTURE);
	ft_bzero(&mlx_data->collectible_sprite, sizeof(t_sprite) * NB_COLLECTIBLE);
	index = 0;
	while (index < MAX_KEY)
	{
		mlx_data->key_press[index] = -1;
		index++;
	}
}
