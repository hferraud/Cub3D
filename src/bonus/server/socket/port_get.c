/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   port_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:35:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/27 01:35:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "socket_bonus.h"

/**
 * @brief Convert char *port to integer
 * @return The port on success, -1 otherwise
 */
int	port_get(const char *ascii_port)
{
	int		port;
	size_t	index;

	port = 0;
	index = 0;
	if (!ft_isdigit(ascii_port[index]))
		return (-1);
	while (ft_isdigit(ascii_port[index]))
	{
		if ((port * 10 + (ascii_port[index] - '0')) / 10 != port)
			return (-1);
		port = port * 10 + ascii_port[index] - '0';
		index++;
	}
	if (ascii_port[index] != '\0')
		return (-1);
	return (port);
}
