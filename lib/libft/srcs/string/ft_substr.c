/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:39:35 by edelage           #+#    #+#             */
/*   Updated: 2022/11/08 15:13:18 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*fresh;
	size_t	len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if ((start + len) > len_s)
		len = len_s - start;
	if (start > len_s)
		len = 0;
	fresh = (char *) malloc(sizeof(char) * (len + 1));
	if (fresh != NULL)
		ft_strlcpy(fresh, &s[start], len + 1);
	return (fresh);
}
