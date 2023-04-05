/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 02:04:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/13 02:04:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_server.h"

static int		is_in_charset(char c, const char *charset);
static size_t	rowlen(const char *str);

/**
 * @brief check if every character in row is in charset
 */
int	is_valid_map_list(t_list *head)
{
	char	*row;

	while (head)
	{
		row = (char *) head->content;
		while (*row)
		{
			if (!is_in_charset(*row, " 01CONSEWLAGRP\n"))
				return (0);
			row++;
		}
		head = head->next;
	}
	return (1);
}

static int	is_in_charset(char c, const char *charset)
{
	size_t	index;

	index = 0;
	while (charset[index] && charset[index] != c)
		index++;
	if (charset[index] != '\0')
		return (1);
	return (0);
}

/**
 * @return Skip all empty lines and return the next lines.
 * @return Return NULL if EOF is encountered.
 * NULL is also return if an error occurred and errno is set
 */
char	*skip_empty_line(int map_fd)
{
	char	*line;

	line = get_next_line(map_fd);
	if (line == NULL)
		return (NULL);
	while (line)
	{
		if (*line != '\n')
			return (line);
		free(line);
		line = get_next_line(map_fd);
		if (line == NULL)
			return (NULL);
	}
	return (NULL);
}

/**
 * @return Return the maximum size of a map row
 */
size_t	get_max_row_size(t_list *head)
{
	size_t	max_size;
	size_t	row_size;

	row_size = rowlen((char *)head->content);
	max_size = row_size;
	while (head)
	{
		row_size = rowlen((char *)head->content);
		if (row_size > max_size)
			max_size = row_size;
		head = head->next;
	}
	return (max_size);
}

/**
 * @return Return the length of a map row in the .cub file
 */
static size_t	rowlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}
