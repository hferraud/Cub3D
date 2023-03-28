/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethan <ethan@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:17:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/26 23:17:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef SOCKET_BONUS_H
# define SOCKET_BONUS_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <errno.h>
# include "error.h"

typedef struct sockaddr_in	t_sockaddr_in;
typedef struct sockaddr		t_sockaddr;

int	port_get(const char *ascii_port);

#endif
