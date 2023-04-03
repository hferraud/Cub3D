/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_send.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:39:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/03 18:39:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"

static size_t	filename_search(char *path);

int	file_send(int client_socket, char *path)
{
}

static int	filename_send(int client_socket, char *path)
{
	const size_t	len_path = ft_strlen(path);
	const size_t	index = filename_search(path);
	size_t			len_filename;
	char			buf;

	len_filename = len_path - index;
	if (write(client_socket, path + index, len_filename) == -1
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == *SOCK_ERROR)
		return (cub_error(CLIENT_ERR_MSG));
	return (0);
}

/**
 * @return The index the beginning of the filename
 */
static size_t	filename_search(char *path)
{
	size_t	index;

	index = ft_strlen(path);
	while (index)
	{
		if (path[index - 1] == '/')
			return (index);
		index--;
	}
	return (0);
}
