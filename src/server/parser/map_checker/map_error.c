/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 23:28:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/25 23:28:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser_server.h"

void	map_error(size_t line, size_t column)
{
	ft_putstr_fd("Error\nMap error at ", STDERR_FILENO);
	ft_putsize_t_fd(line, STDERR_FILENO);
	ft_putstr_fd(", ", STDERR_FILENO);
	ft_putsize_t_fd(column, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}
