/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 03:04:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 03:04:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "error.h"

/**
 * @brief Print the error message, use errno if error_msg is NULL.
 * @return Always return -1
 */
int	cub_error(char *error_msg)
{
	write(STDERR_FILENO, "Error\n", 6);
	if (error_msg == NULL)
		perror(NULL);
	else
		ft_putstr_fd(error_msg, STDERR_FILENO);
	return (-1);
}
