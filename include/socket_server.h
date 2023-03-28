/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_server.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:13:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/27 01:13:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef SOCKET_SERVER_H
# define SOCKET_SERVER_H

# include <ifaddrs.h>
# include <netdb.h>
# include "socket_bonus.h"

typedef struct ifaddrs	t_ifaddrs;

int	socket_init(const char *ascii_port, int n);

#endif
