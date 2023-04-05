/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collectible.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:35:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/05 16:35:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "collectible.h"
#include "map_client.h"

static t_collectible	*collectible_new(t_collectible_id id, t_fvector pos);

int	collectible_append(t_collectible **head, t_collectible_id id, t_fvector pos)
{
	t_collectible	*elem;

	elem = collectible_new(id, pos);
	if (elem == NULL)
		return (perror("collectible_new()"), -1);
	elem->next = *head;
	*head = elem;
	return (0);
}

static t_collectible	*collectible_new(t_collectible_id id, t_fvector pos)
{
	t_collectible	*new;

	new = (t_collectible *) malloc(sizeof(t_collectible));
	if (new == NULL)
		return (NULL);
	new->id = id;
	new->pos = pos;
	new->next = NULL;
	return (new);
}

void	collectible_clear(t_collectible *head)
{
	t_collectible	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

int	is_collectible(char cell)
{
	return (cell == MEDIC_KIT
		|| cell == AMMO
		|| cell == PISTOL
		|| cell == ASSAULT_RIFLE);
}
