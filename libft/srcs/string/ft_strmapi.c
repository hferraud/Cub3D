/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:30:47 by edelage           #+#    #+#             */
/*   Updated: 2022/11/07 21:03:45 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*fresh;
	size_t	index;
	size_t	len;

	if (s == NULL || f == NULL)
		return (NULL);
	len = ft_strlen(s);
	index = 0;
	fresh = (char *) malloc(sizeof(char) * (len + 1));
	if (fresh == NULL)
		return (NULL);
	while (s[index])
	{
		fresh[index] = (*f)(index, s[index]);
		index++;
	}
	fresh[index] = '\0';
	return (fresh);
}
