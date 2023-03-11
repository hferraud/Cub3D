/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:53:24 by edelage           #+#    #+#             */
/*   Updated: 2022/09/24 22:31:22 by edelage          ###   ########lyon.fr   */
/*   Updated: 2022/09/17 11:07:20 by edelage          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			index;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	index = 0;
	ptr_s1 = (unsigned char *) s1;
	ptr_s2 = (unsigned char *) s2;
	while (index < n)
	{
		if (ptr_s1[index] != ptr_s2[index])
			return (ptr_s1[index] - ptr_s2[index]);
		index++;
	}
	return (0);
}
