/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:42:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/09 19:42:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	parser_error(char *str);

int	parser(int argc, char **argv, t_map *map)
{
	int		map_fd;

	if (argc < 2)
        return (parser_error("Too few argument\n"));
    else if (argc > 2)
        return (parser_error("Too many argument\n"));
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd == -1)
		return (parser_error(NULL));
	close(map_fd);
}


static int	parser_error(char *error_msg)
{
    if (error_msg == NULL)
        perror("Error");
	else
    {
        write(STDERR_FILENO, "Error\n", 6);
        ft_putstr_fd(error_msg, STDERR_FILENO);
    }
    return (-1);
}
