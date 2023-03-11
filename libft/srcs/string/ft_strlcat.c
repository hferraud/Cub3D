/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:06:14 by edelage           #+#    #+#             */
/*   Updated: 2022/11/08 00:05:20 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	const size_t	len_dest = ft_strlen(dest);

	if ((len_dest + 1) > size)
		return (size + ft_strlen(src));
	ft_strlcpy(&(dest[len_dest]), src, size - len_dest);
	return (len_dest + ft_strlen(src));
}
