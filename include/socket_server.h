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

# include "socket_bonus.h"

int	socket_init(const char *ip, const char *ascii_port);

#endif
