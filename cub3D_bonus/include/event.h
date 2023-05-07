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
	EVENT_OPEN_DOOR,
	EVENT_CLOSE_DOOR,
	EVENT_DEATH,
	EVENT_TAKE_COLLECTIBLE,
};

struct s_event
{
	t_event_id	id;
	t_vector	position;
};

#endif
