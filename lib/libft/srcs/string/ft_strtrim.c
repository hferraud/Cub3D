/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 23:30:47 by edelage           #+#    #+#             */
/*   Updated: 2022/11/08 16:23:54 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	is_set(char const *set, int c)
{
	size_t	index;

	index = 0;
	while (set[index])
	{
		if (set[index] == c)
			return (1);
		index++;
	}
	return (0);
}

static int	len_word(char const *s, char const *set, int *i_start, int *i_end)
{
	while (*i_end != 0 && is_set(set, s[*i_end]) == 1)
		(*i_end)--;
	while (s[*i_start] && is_set(set, s[*i_start]) == 1)
		(*i_start)++;
	return (*i_end - *i_start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*fresh;
	int		len;
	int		i;
	int		end_i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	end_i = ft_strlen(s1) - 1;
	len = len_word(s1, set, &i, &end_i);
	if (len < 0)
		len = 0;
	fresh = (char *) malloc(sizeof(char) * (len + 1));
	if (fresh == NULL)
		return (NULL);
	len = 0;
	while (i <= end_i)
	{
		fresh[len] = s1[i];
		len++;
		i++;
	}
	fresh[len] = '\0';
	return (fresh);
}
