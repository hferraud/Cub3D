/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:48:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/07 21:48:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "collectible.h"
#include "define.h"

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
