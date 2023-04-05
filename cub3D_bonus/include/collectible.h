/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:25:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/05 16:25:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef COLLECTIBLE_H
# define COLLECTIBLE_H

# include <stdlib.h>
# include "vector.h"

# define MEDIC_KIT_PATH			"asset/life_pack.xpm"
# define AMMO_PATH				"asset/ammo.xpm"
# define PISTOL_PATH			"asset/pistol.xpm"
# define ASSAULT_RIFFLE_PATH	"asset/assault_riffle.xpm"

# define NB_COLLECTIBLE		4
# define MEDIC_KIT_OFFSET	0.1
# define AMMO_OFFSET		0.1

typedef enum e_collectible_id	t_collectible_id;
typedef struct s_collectible	t_collectible;

enum e_collectible_id
{
	LIFE_PACK_ID,
	AMMO_ID,
	PISTOL_ID,
	ASSAULT_RIFFLE_ID
};

struct s_collectible
{
	t_collectible_id	id;
	t_fvector			pos;
	t_collectible		*next;
};

int		collectible_append(t_collectible **head, t_collectible_id id,
			t_fvector pos);
void	collectible_clear(t_collectible *head);
int		is_collectible(char cell);

#endif
