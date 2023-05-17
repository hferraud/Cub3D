/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 03:08:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/14 03:08:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdio.h>
# include "libft.h"

# define CLIENT_LOST	"Connection with client lost\n"
# define CLIENT_ERR_MSG	"Error in client\n"
# define SERVER_LOST	"Connection with server lost\n"

int	cub_error(char *error_msg);

#endif
