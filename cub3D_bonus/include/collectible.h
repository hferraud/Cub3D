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
# include <stdio.h>
# include "vector.h"

# define MEDIC_KIT_PATH			"asset/medic_kit.xpm"
# define AMMO_PATH				"asset/ammo.xpm"
# define PISTOL_PATH			"asset/pistol.xpm"
# define ASSAULT_RIFFLE_PATH	"asset/assault_rifle.xpm"

# define NB_COLLECTIBLE		4
# define COLLECTIBLE_OFFSET	0.5

typedef enum e_collectible_id		t_collectible_id;
typedef struct s_collectible		t_collectible;
typedef struct s_collectible_list	t_collectible_list;

enum e_collectible_id
{
	MEDIC_KIT_ID,
	AMMO_ID,
	PISTOL_ID,
	ASSAULT_RIFFLE_ID,
	UNDEFINED
};

struct s_collectible
{
	t_collectible_id	id;
	t_fvector			pos;
	t_fvector			relative_pos;
	float				dist;
};

struct s_collectible_list
{
	t_collectible_id	id;
	t_fvector			pos;
	t_collectible_list	*next;
};

t_collectible		collectible_init(t_collectible_id id, t_fvector pos);
int					collectible_append(t_collectible_list **head,
						t_collectible_id id, t_fvector pos);
void				collectible_list_clear(t_collectible_list *head);
size_t				collectible_list_length(t_collectible_list *list);
t_collectible_id	collectible_id_get(char cell);

#endif
