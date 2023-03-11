/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 17:08:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/29 17:08:00 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	return_error(int error_code)
{
	errno = error_code;
	return (-1);
}

long long	ft_atoll(const char *nptr)
{
	size_t		index;
	int			sign;
	long long	result;

	index = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(nptr[index]))
		index++;
	if (ft_issign(nptr[index]))
	{
		if (nptr[index] == '-')
			sign = -1;
		index++;
	}
	while (ft_isdigit(nptr[index]))
	{
		if ((result * 10 + (nptr[index] - '0') * sign) / 10 != result)
			return (return_error(ERANGE));
		result = result * 10 + (nptr[index] - '0') * sign;
		index++;
	}
	return (result);
}
