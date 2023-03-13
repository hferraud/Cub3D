/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 03:01:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/13 03:01:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	len_nb(size_t n)
{
	if (n > 9)
		return (len_nb(n / 10) + 1);
	else
		return (1);
}

static void	fill(size_t n, char *fresh, size_t *len_n)
{
	if (n > 9)
	{
		fresh[*len_n] = n % 10 + '0';
		*len_n -= 1;
		fill((n / 10), fresh, len_n);
	}
	else
	{
		fresh[*len_n] = n + '0';
	}
}

char	*ft_stoa(size_t n)
{
	char	*fresh;
	size_t	len_n;

	len_n = len_nb(n);
	fresh = (char *) malloc(sizeof(char) * (len_n + 1));
	if (fresh == NULL)
		return (NULL);
	fresh[len_n] = '\0';
	len_n--;
	fill(n, fresh, &len_n);
	return (fresh);
}
