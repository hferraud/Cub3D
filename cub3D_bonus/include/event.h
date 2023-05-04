/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:13:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/02 17:13:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef EVENT_H
# define EVENT_H

# include "vector.h"

typedef struct s_event			t_event;
typedef enum e_event_id			t_event_id;

enum	e_event_id
{
	EVENT_DOOR_INTERACTION,
	EVENT_SHOOT,
	EVENT_TAKE_MEDIC_KIT,
	EVENT_TAKE_AMMO,
	EVENT_TAKE_PISTOL,
	EVENT_TAKE_ASSAULT,
};

struct s_event
{
	t_event_id	id;
	t_vector	position;
};

#endif
