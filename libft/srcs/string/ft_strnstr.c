/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 17:47:42 by edelage           #+#    #+#             */
/*   Updated: 2022/11/07 14:04:42 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	len_s1;
	size_t	len_s2;
	size_t	index;

	index = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	if (len_s2 == 0)
		return ((char *) s1);
	while (s1[index] && index + len_s2 <= n && index + len_s2 <= len_s1)
	{
		if (ft_strncmp((char *) &s1[index], s2, len_s2) == 0)
			return ((char *) &s1[index]);
		index++;
	}
	return (NULL);
}
