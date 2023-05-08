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
# include "libft.h"

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

typedef struct s_cub	t_cub;

t_list	*new_event(t_event event_data);
void	add_collectible_event(t_cub *cub);
void	add_door_event(t_cub *cub, t_vector map_pos, char door_state);

#endif
