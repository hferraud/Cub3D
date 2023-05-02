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
#include "collectible.h"

static t_collectible_list	*collectible_new(t_collectible_id id, t_fvector pos);

int	collectible_append(t_collectible_list **head, t_collectible_id id, t_fvector pos)
{
	t_collectible_list	*elem;

	elem = collectible_new(id, pos);
	if (elem == NULL)
		return (perror("collectible_new()"), -1);
	elem->next = *head;
	*head = elem;
	return (0);
}

static t_collectible_list	*collectible_new(t_collectible_id id, t_fvector pos)
{
	t_collectible_list	*new;

	new = (t_collectible_list *) malloc(sizeof(t_collectible_list));
	if (new == NULL)
		return (NULL);
	new->id = id;
	new->pos = pos;
	new->next = NULL;
	return (new);
}

void	collectible_list_clear(t_collectible_list *head)
{
	t_collectible_list	*next;

	while (head)
	{
		next = head->next;
		free(head);
		head = next;
	}
}

size_t	collectible_list_length(t_collectible_list *list)
{
	size_t	count;

	count = 0;
	while (list)
	{
		count++;
		list = list->next;
	}
	return (count);
}
