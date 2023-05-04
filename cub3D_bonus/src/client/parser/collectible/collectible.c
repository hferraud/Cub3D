/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mururoah <mururoah@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 19:57:00 by mururoah          #+#    #+#             */
/*   Updated: 2023/05/02 19:57:00 by mururoah         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "collectible.h"
#include "map_client.h"

t_collectible	collectible_init(t_collectible_id id, t_fvector pos)
{
	t_collectible	collectible;

	collectible.id = id;
	collectible.pos = pos;
	return (collectible);
}

t_collectible_id	collectible_id_get(char cell)
{
	const t_collectible_id	id[4]
		= {MEDIC_KIT_ID, AMMO_ID, PISTOL_ID, ASSAULT_RIFFLE_ID};
	const char				cells[4] = {LIFE_PACK, AMMO, PISTOL, ASSAULT_RIFLE};
	int						i;

	i = 0;
	while (i < 4)
	{
		if (cells[i] == cell)
			return (id[i]);
		i++;
	}
	return (UNDEFINED);
}
