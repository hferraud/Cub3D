/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 13:16:55 by edelage           #+#    #+#             */
/*   Updated: 2022/09/07 00:52:40 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	size_t	index;

	index = 0;
	ptr = (char *) s;
	while (index < n)
	{
		ptr[index] = c;
		index++;
	}
	return (s);
}
