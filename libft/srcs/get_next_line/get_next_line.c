/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:41:28 by edelage           #+#    #+#             */
/*   Updated: 2022/11/11 18:26:11 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*gnl_subline(char *str, char *stack, int fd, int end_line)
{
	char	*line;
	char	*tmp;

	if (fd < 0 || end_line < 0)
		return (NULL);
	line = ft_substr(str, 0, end_line + 1);
	if (line == NULL)
		return (NULL);
	tmp = ft_substr(str, end_line + 1, ft_strlen(str) - end_line);
	if (tmp == NULL)
	{
		free(line);
		return (NULL);
	}
	init_str(stack, BUFFER_SIZE + 1);
	ft_strlcpy(stack, tmp, BUFFER_SIZE + 1);
	free(tmp);
	if (str != stack)
		free(str);
	return (line);
}

char	*gnl_strjoin_free(char *s1, const char *s2)
{
	char	*new;
	size_t	index;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new = (char *) malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (new == NULL)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(new, s1, len_s1 + len_s2 + 1);
	index = 0;
	while (s2[index])
	{
		new[len_s1 + index] = s2[index];
		index++;
	}
	new[len_s1 + index] = '\0';
	free(s1);
	return (new);
}

char	*gnl_read_line(int fd, char *line, char *buffer)
{
	size_t	ret;

	ret = BUFFER_SIZE;
	while (ret == BUFFER_SIZE && strichr(line, '\n') == -1)
	{
		init_str(buffer, BUFFER_SIZE + 1);
		ret = read(fd, buffer, BUFFER_SIZE);
		line = gnl_strjoin_free(line, buffer);
		if (line == NULL)
			return (NULL);
		init_str(buffer, BUFFER_SIZE + 1);
	}
	return (line);
}

char	*gnl_line(char *stack, int fd)
{
	char	*line;

	if (stack[0] != '\0')
	{
		line = (char *) malloc(sizeof(char) * (ft_strlen(stack) + 1));
		if (line == NULL)
			return (NULL);
		ft_strlcpy(line, stack, ft_strlen(stack) + 1);
		init_str(stack, BUFFER_SIZE + 1);
	}
	else
	{
		line = (char *) malloc(sizeof(char));
		if (line == NULL)
			return (NULL);
		line[0] = '\0';
	}
	line = gnl_read_line(fd, line, stack);
	if (line == NULL)
		return (NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	int			end_line;
	char		*line;
	static char	stack[OPEN_MAX][BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	if (*stack[fd])
	{
		end_line = strichr(stack[fd], '\n');
		if (end_line != -1)
			return (gnl_subline(stack[fd], stack[fd], fd, end_line));
	}
	line = gnl_line(stack[fd], fd);
	if (line == NULL)
		return (NULL);
	end_line = strichr(line, '\n');
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	if (end_line != -1 && end_line < (int)(ft_strlen(line) - 1))
		line = gnl_subline(line, stack[fd], fd, end_line);
	return (line);
}
