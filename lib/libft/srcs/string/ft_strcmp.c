/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 16:47:00 by edelage           #+#    #+#             */
/*   Updated: 2023/01/13 16:47:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	index;

	index = 0;
	while (s1[index] && s2[index]
		&& (unsigned char)s1[index] == (unsigned char)s2[index])
		index++;
	return ((unsigned char) s1[index] - (unsigned char)s2[index]);
}
