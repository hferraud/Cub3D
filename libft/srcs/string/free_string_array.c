/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 00:57:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/13 00:57:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

void	free_string_array(char **array)
{
	size_t	index;

	index = 0;
	if (array == NULL)
		return ;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}
