/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content_send.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 23:50:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/13 23:50:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

int	file_content_send(int client_socket, int fd)
{
	char	buf[SOCK_BUFFER_SIZE];
	ssize_t	ret;

	ret = SOCK_BUFFER_SIZE;
	while (ret == SOCK_BUFFER_SIZE)
	{
		ret = read(fd, buf, SOCK_BUFFER_SIZE);
		if (ret == -1)
		{
			close(fd);
			return (cub_error("Error during reading texture file\n"), 1);
		}
		if (write(client_socket, buf, ret) == -1)
			return (close(fd), cub_error(CLIENT_LOST));
	}
	return (0);
}
