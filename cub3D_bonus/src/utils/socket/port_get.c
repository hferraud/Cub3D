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
#include "cub_socket.h"

static int	return_set_errno(int errno_code, int return_value);

/**
 * @brief Convert char *port to integer
 * @return The port on success. On error 0 is returned, and errno is set
 */
uint16_t	port_get(const char *ascii_port)
{
	uint16_t	port;
	size_t		index;

	port = 0;
	index = 0;
	if (!ft_isdigit(ascii_port[index]))
		return (return_set_errno(EINVAL, 0));
	while (ft_isdigit(ascii_port[index]))
	{
		if (((uint16_t)(port * 10 + (ascii_port[index] - '0')) / 10) != port)
			return (return_set_errno(EOVERFLOW, 0));
		port = port * 10 + ascii_port[index] - '0';
		index++;
	}
	if (ascii_port[index] != '\0')
		return (return_set_errno(EINVAL, 0));
	return (port);
}

static int	return_set_errno(int errno_code, int return_value)
{
	errno = errno_code;
	return (return_value);
}
