/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 18:39:00 by ethan             #+#    #+#             */
/*   Updated: 2023/04/03 18:39:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_client.h"

static int	filename_parse(char **path, int server_socket);
static int	file_request(char *path, int server_socket);
static int	file_receive(int file_fd, int server_socket);

int	file_parse(t_map_client *map, int server_socket)
{
	t_texture_id	id;
	int				file_fd;
	int				req_code;

    //TODO O3
	id = 0;
	while (id != UNDEFINED_ID)
	{
		if (filename_parse(&map->path[id], server_socket) == -1)
			return (write(server_socket, SOCK_ERROR, 1), -1);
		req_code = file_request(map->path[id], server_socket);
		if (req_code == -1)
			return (write(server_socket, SOCK_ERROR, 1), -1);
		if (req_code == 0)
		{
			file_fd = open(map->path[id], O_WRONLY | O_CREAT, 0644);
			if (file_fd == -1)
				return (cub_error(NULL));
			printf("Loading %s\n", map->path[id]);
			if (file_receive(file_fd, server_socket) == -1)
				return (close(file_fd), -1);

			printf("%s successfully loaded\n", map->path[id]);
			close(file_fd);
		}
		id++;
	}
	return (0);
}

static int	filename_parse(char **path, int server_socket)
{
	size_t	size;
	size_t	dir_len;

	printf("Loading texture file name\n");
	if (read(server_socket, &size, sizeof(size_t)) <= 0)
		return (cub_error(SERVER_LOST));
	dir_len = ft_strlen(DIR_SPRITE);
	size += dir_len;
	*path = malloc((size + 1) * sizeof(char));
	if (*path == NULL)
		return (cub_error(NULL));
	ft_strcpy(*path, DIR_SPRITE);
	if (write(server_socket, SOCK_SUCCESS, 1) == -1)
		return (cub_error(SERVER_LOST));
	if (read(server_socket, *path + dir_len, size * sizeof(char)) <= 0)
		return (cub_error(SERVER_LOST));
	(*path)[size] = '\0';
	return (0);
}

/**
 * Send a request to the server if the file is missing
 * @return 0 if the file does not exist, 1 if the file can be read.
 * Return -1 if the file cannot be accessed or if an error occurred
 */
static int	file_request(char *path, int server_socket)
{
	if (access(path, R_OK) == -1)
	{
		if (errno == ENOENT)
		{
			errno = 0;
			printf("Requesting %s\n", path);
			if (write(server_socket, SOCK_SUCCESS, 1) == -1)
				return (cub_error(SERVER_LOST));
			return (0);
		}
		return (cub_error(NULL));
	}
	printf("%s already loaded\n", path);
	if (write(server_socket, FILE_EXIST, 1) == -1)
		return (cub_error(SERVER_LOST));
	return (1);
}

static int	file_receive(int file_fd, int server_socket)
{
	ssize_t	size;
	char	*buffer[SOCK_BUFFER_SIZE];
	ssize_t	read_size;
	ssize_t	count;

	if (read(server_socket, &size, sizeof(size_t)) == -1)
		return (cub_error(SERVER_LOST));
	count = 0;
	while (count < size)
	{
		if (count + SOCK_BUFFER_SIZE > size)
			read_size = size - count;
		else
			read_size = SOCK_BUFFER_SIZE;
		if (read(server_socket, buffer, read_size) < read_size)
			return (cub_error("file_receive()\n"));
		if (write(file_fd, buffer, read_size) == -1)
			return (cub_error("file_receive()\n"));
		count += read_size;
	}
	if (write(server_socket, SOCK_SUCCESS, 1) == -1)
		return (cub_error(SERVER_LOST));
	return (0);
}
