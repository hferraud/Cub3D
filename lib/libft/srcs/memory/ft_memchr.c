/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:47:54 by edelage           #+#    #+#             */
/*   Updated: 2022/10/11 19:46:19 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			index;

	index = 0;
	ptr = (unsigned char *) s;
	while (index < n)
	{
		if (ptr[index] == (unsigned char) c)
			return ((void *) &ptr[index]);
		index++;
	}
	return (NULL);
}
