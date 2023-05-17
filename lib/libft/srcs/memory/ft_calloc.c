/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:48:20 by edelage           #+#    #+#             */
/*   Updated: 2022/11/08 23:06:26 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return ((void *) malloc(0));
	if (SIZE_MAX / nmemb < size)
		return (NULL);
	ptr = (void *) malloc(size * nmemb);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, size * nmemb);
	return (ptr);
}
