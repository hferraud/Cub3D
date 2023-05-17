/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:10:33 by edelage           #+#    #+#             */
/*   Updated: 2022/09/07 00:52:30 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	index;

	index = 0;
	if (dest < src)
	{
		while (index < n)
		{
			((char *) dest)[index] = ((char *) src)[index];
			index++;
		}
	}
	else
	{
		while (n)
		{
			((char *) dest)[n - 1] = ((char *) src)[n - 1];
			n--;
		}
	}
	return (dest);
}
