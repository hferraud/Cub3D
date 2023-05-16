/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 05:00:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/16 05:00:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "server_data.h"
#include <signal.h>

extern t_server_data	*g_server_data;

void	server_exit(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		server_data_destroy(g_server_data);
		exit(0);
	}
}
