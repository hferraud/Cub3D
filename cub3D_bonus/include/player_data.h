/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 14:55:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/02 14:55:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PLAYER_DATA_H
# define PLAYER_DATA_H

# include "event.h"
# include "player.h"
# include <stdbool.h>

typedef struct s_player_data	t_player_data;

struct s_player_data
{
	bool			update;
	pthread_mutex_t	*update_lock;
	t_player		player;
	t_list			*events;
	pthread_mutex_t	*events_lock;
};

#endif
