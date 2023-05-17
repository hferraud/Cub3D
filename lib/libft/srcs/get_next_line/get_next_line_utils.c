/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:46:28 by edelage           #+#    #+#             */
/*   Updated: 2022/10/11 18:19:26 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	init_str(char *str, size_t size)
{
	size_t	count;

	count = 0;
	while (count < size)
	{
		str[count] = '\0';
		count++;
	}
}

int	strichr(const char *str, int c)
{
	int	index;

	index = 0;
	if (!str)
		return (-1);
	while (str[index])
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	if (str[index] == c)
		return (index);
	return (-1);
}
