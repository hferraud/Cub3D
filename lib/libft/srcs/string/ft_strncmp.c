/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:42:47 by edelage           #+#    #+#             */
/*   Updated: 2022/09/25 20:34:39 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	index;

	index = 0;
	if (n == 0)
		return (0);
	while (index < (n - 1) && s1[index] && s2[index]
		&& (unsigned char)s1[index] == (unsigned char)s2[index])
		index++;
	return ((unsigned char)s1[index] - (unsigned char)s2[index]);
}
