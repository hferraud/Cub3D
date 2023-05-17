/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:26:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/13 17:26:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t	*mutex_init(void)
{
	pthread_mutex_t	*mutex;

	mutex = malloc(sizeof(pthread_mutex_t));
	if (mutex == NULL)
		return (NULL);
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		free(mutex);
		return (NULL);
	}
	return (mutex);
}
