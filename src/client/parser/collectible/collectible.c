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
