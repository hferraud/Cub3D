/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:13:26 by edelage           #+#    #+#             */
/*   Updated: 2022/11/07 13:47:03 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	index;

	index = 0;
	dup = (char *) malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (dup == NULL)
		return (NULL);
	while (s[index])
	{
		dup[index] = s[index];
		index++;
	}
	dup[index] = '\0';
	return (dup);
}
