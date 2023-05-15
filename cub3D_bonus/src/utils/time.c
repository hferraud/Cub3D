/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:27:00 by ethan             #+#    #+#             */
/*   Updated: 2023/05/11 11:27:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <sys/time.h>

size_t	elapsed_time(struct timeval start_time, struct timeval current_time)
{
	return ((size_t)(current_time.tv_sec - start_time.tv_sec) * 1000000
			+ (current_time.tv_usec - start_time.tv_usec));
}
