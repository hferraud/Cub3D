/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 18:57:11 by edelage           #+#    #+#             */
/*   Updated: 2022/11/07 22:45:45 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	len_nb(int n)
{
	if (n < -9)
		return (len_nb(-(n / 10)) + 2);
	else if (n < 0)
		return (2);
	else if (n > 9)
		return (len_nb(n / 10) + 1);
	else
		return (1);
}

static void	fill(int n, char *fresh, size_t *len_n)
{
	if (n < 0)
	{
		fresh[0] = '-';
		fresh[*len_n] = (-(n % 10) + '0');
		*len_n -= 1;
		if (-(n / 10) != 0)
			fill(-(n / 10), fresh, len_n);
	}
	else if (n > 9)
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

char	*ft_itoa(int n)
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
