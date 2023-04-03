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

static int		filename_send(int client_socket, char *path);
static size_t	filename_search(char *path);
static int		content_send(int client_socket, char *path);
static int		file_open(char *path, int *fd, struct stat *stat_buf);

/**
 * @brief Send a file to a client
 * @return 0 on success, -1 if there was an error in the client
 * and 1 if it is a server error
 */
int	file_send(int client_socket, char *path)
{
	int			ret;

	ret = filename_send(client_socket, path);
	if (ret == -1)
		return (-1);
	else if (ret == 1)
		return (0);
	ret = content_send(client_socket, path);
	if (ret == -1 || ret == 1)
		return (ret);
	return (0);
}

/**
 * @brief Send the filename to the client
 * @return 1 if the client already has the file,
 * 0 if the client does not have the file or -1 in case of errors
 */
static int	filename_send(int client_socket, char *path)
{
	const size_t	len_path = ft_strlen(path);
	const size_t	index = filename_search(path);
	size_t			len_filename;
	char			buf;

	len_filename = len_path - index;
	if (write(client_socket, &len_filename, sizeof(size_t)) == -1
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == *SOCK_ERROR)
		return (cub_error(CLIENT_ERR_MSG));
	if (write(client_socket, path + index, len_filename) == -1
		|| read(client_socket, &buf, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (buf == *SOCK_ERROR)
		return (cub_error(CLIENT_ERR_MSG));
	else if (buf == *FILE_EXIST)
	{
		printf("The client already has the texture file: %s\n", path + index);
		return (1);
	}
	return (0);
}

/**
 * @brief Send the content of the file to the client
 * @return 0 on success, -1 if there was an error in the client
 * and 1 if it is a server error
 */
static int	content_send(int client_socket, char *path)
{
	char		buf[SOCK_BUFFER_SIZE];
	ssize_t		ret;
	int			fd;
	struct stat	stat_buf;
	size_t		file_size;
	char		receive;

	if (file_open(path, &fd, &stat_buf) == -1)
		return (1);
	file_size = stat_buf.st_size;
	if (write(client_socket, &file_size, sizeof(size_t)) == -1)
		return (close(fd), cub_error(CLIENT_LOST));
	ret = 1028;
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
	if (read(client_socket, &receive, sizeof(char)) <= 0)
		return (cub_error(CLIENT_LOST));
	if (receive != *SOCK_SUCCESS)
		return (cub_error(CLIENT_ERR_MSG));
	printf("Texture file %s send\n", path);
	return (close(fd), 0);
}

static int	file_open(char *path, int *fd, struct stat *stat_buf)
{
	*fd = open(path, O_RDONLY);
	if (*fd == -1)
		return (cub_error("Error while opening file\n"));
	if (fstat(*fd, stat_buf) == -1)
	{
		close(*fd);
		return (perror("fstat()\n"), -1);
	}
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
