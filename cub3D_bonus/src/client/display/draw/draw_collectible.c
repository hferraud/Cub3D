/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw_collectible.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: ethan <ethan@student.42lyon.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2023/04/05 17:46:00 by ethan			 #+#	#+#			 */
/*   Updated: 2023/04/05 17:46:00 by ethan			###   ########lyon.fr   */
/*  sd																		 */
/* ************************************************************************** */
#include <stdbool.h>
#include "collectible.h"
#include "cub.h"
#include "draw.h"

static void		draw_collectible_sprite(t_cub *cub, t_collectible collectible);
static void		collectible_set_dist(t_cub *cub);
static void		sort_collectible(t_cub *cub);

void	draw_collectible(t_cub *cub)
{
	size_t	i;

	collectible_set_dist(cub);
	sort_collectible(cub);
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		draw_collectible_sprite(cub, cub->map.collectible_data.collectible[i]);
		i++;
	}
}

static void	draw_collectible_sprite(t_cub *cub, t_collectible collectible)
{
	t_sprite	texture;
	t_fvector	sprite;
	t_fvector	draw_start;
	t_fvector	draw_end;
	int		sprite_screen_x;
	int		sprite_screen_y;
	int		sprite_texture_y;
	int		sprite_texture_x;
	float		height;
	float		width;
	float		inverse_det;
	int		 color;

	inverse_det = 1.f / (cub->player.camera.x * cub->player.rotation.y
			- cub->player.rotation.x * cub->player.camera.y);
	sprite.x = inverse_det * (cub->player.rotation.y * collectible.relative_pos.x
			- cub->player.rotation.x * collectible.relative_pos.y);
	sprite.y = inverse_det * (-cub->player.camera.y * collectible.relative_pos.x
			+ cub->player.camera.x * collectible.relative_pos.y);
	sprite_screen_x = (int)(WIN_WIDTH / 2 * (1 + sprite.x / sprite.y));
	height = abs(((int)(WIN_HEIGHT / (sprite.y * 2))));
	width = abs(((int)(WIN_WIDTH / (sprite.y * 2))));
//	printf("screen_x: %f height: %f dist: %f\n", sprite_screen_x, height, sprite.y);
	draw_start.y = WIN_HEIGHT / 2 - height / 2;
	if (draw_start.y > WIN_HEIGHT)
		draw_start.y = WIN_HEIGHT - 1;
	draw_end.y = WIN_HEIGHT / 2 + height / 2;
	if (draw_end.y < 0)
		draw_end.y = 0;
	texture = cub->mlx_data->collectible_sprite[MEDIC_KIT_ID];
	draw_start.x = sprite_screen_x - width / 2;
	draw_end.x = sprite_screen_x + width / 2;
//	printf("screen_pos: x %.1f y %.1f end %f start %f\n", sprite_screen_x, sprite_screen_y, draw_end.y, draw_start.y);
	sprite_screen_x = draw_start.x;
	while (sprite_screen_x < draw_end.x)
	{
		sprite_texture_x = (sprite_screen_x - draw_start.x) * texture.width / width;
		sprite_screen_y = draw_start.y;
		while (sprite_screen_y < draw_end.y && sprite_screen_y < WIN_HEIGHT)
		{
			sprite_texture_y = (sprite_screen_y - draw_start.y) * texture.height / height;
//		printf("texture: x %d y %d\n", sprite_texture_x, sprite_texture_y);
//		printf("screen: x %d y %.d\n", sprite_screen_x, sprite_screen_y);
//		printf("texture bound: h %d w %d\n\n", texture.height, texture.width);
			color = *(int *) (texture.img_data.addr + sprite_texture_x * texture.img_data.bit_ratio + sprite_texture_y * texture.img_data.line_length);
			mlx_put_pixel(&cub->mlx_data->img_data, sprite_screen_x, sprite_screen_y, color);
			sprite_screen_y++;
		}
		sprite_screen_x++;
	}
	//printf("sprite %f %f\n", sprite.x, sprite.y);
}

static void	draw_collectible_stripe(t_cub *cub, t_sprite sprite)
{

}

/**
 * @brief Set the distance from the player of all collectibles
 */
static void collectible_set_dist(t_cub *cub)
{
	size_t			i;
	t_collectible	*collectibles;

	collectibles = cub->map.collectible_data.collectible;
	i = 0;
	while (i < cub->map.collectible_data.size)
	{
		collectibles[i].relative_pos = fvector_sub(cub->player.pos, collectibles->pos);
		collectibles[i].dist = collectibles->relative_pos.x * collectibles->relative_pos.x
				+ collectibles->relative_pos.y * collectibles->relative_pos.y;
		i++;
	}
}

/**
 * @brief Sort all collectibles from the nearest to the further away of the player
 */
static void	sort_collectible(t_cub *cub)
{
	t_collectible	*collectible;
	t_collectible	tmp;
	bool			flag;
	size_t			i;

	collectible = cub->map.collectible_data.collectible;
	flag = true;
	while (flag)
	{
		flag = false;
		i = 1;
		while (i < cub->map.collectible_data.size)
		{
			if (collectible[i].dist > collectible[i - 1].dist)
			{
				flag = true;
				tmp = collectible[i];
				collectible[i] = collectible[i - 1];
				collectible[i - 1] = tmp;
			}
			i++;
		}
	}
}
