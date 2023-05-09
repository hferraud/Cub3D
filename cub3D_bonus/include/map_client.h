/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_client.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 16:36:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/02 16:36:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef MAP_CLIENT_H
# define MAP_CLIENT_H

# include <sys/types.h>
# include <stdlib.h>
# include "libft.h"
# include "collectible.h"
# include "define.h"

# define DIR_SPRITE		"asset/"

typedef struct s_map_client			t_map_client;
typedef struct s_spawn				t_spawn;
typedef struct s_collectible		t_collectible;
typedef struct s_collectible_list	t_collectible_list;
typedef struct s_collectible_data	t_collectible_data;

struct s_spawn
{
	size_t	x;
	size_t	y;
	char	orientation;
};

struct s_collectible_data
{
	pthread_mutex_t	*collectible_lock;
	t_collectible	*collectible;
	size_t			size;
};

struct s_map_client
{
	char				**map;
	pthread_mutex_t		*map_lock;
	size_t				height;
	size_t				width;
	t_spawn				spawn;
	t_collectible_data	collectible_data;
	char				*path[7];
};

void	map_clear(t_map_client *map);

#endif
