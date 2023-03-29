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
#include "my_socket.h"

/**
 * @brief Convert char *port to integer
 * @return The port on success. On error 0 is returned, and errno is set
 */
uint16_t port_get(const char *ascii_port)
{
	uint16_t	port;
	size_t		index;

	port = 0;
	index = 0;
	if (!ft_isdigit(ascii_port[index]))
	{
		errno = EINVAL;
		return (0);
	}
	while (ft_isdigit(ascii_port[index]))
	{
		if ((port * 10 + (ascii_port[index] - '0')) / 10 != port)
		{
			errno = EOVERFLOW;
			return (0);
		}
		port = port * 10 + ascii_port[index] - '0';
		index++;
	}
	if (ascii_port[index] != '\0')
	{
		errno = EINVAL;
		return (0);
	}
	return (port);
}
