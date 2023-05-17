/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_client.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:26:00 by edelage           #+#    #+#             */
/*   Updated: 2023/03/28 22:26:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef SOCKET_CLIENT_H
# define SOCKET_CLIENT_H

# include "cub_socket.h"

typedef struct hostent	t_hostent;

int	socket_client_init(int argc, char **argv);

#endif
