/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:07:32 by edelage           #+#    #+#             */
/*   Updated: 2022/11/08 17:08:05 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	size_t	len_s1;
	size_t	len_s2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	fresh = (char *) malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (fresh == NULL)
		return (NULL);
	ft_memcpy((void *) fresh, (void *) s1, len_s1);
	ft_strlcpy(&(fresh[len_s1]), s2, len_s2 + 1);
	return (fresh);
}
