/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_client.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:22:00 by edelage           #+#    #+#             */
/*   Updated: 2023/04/01 15:22:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_CLIENT_H
# define PARSER_CLIENT_H

# include "cub.h"

int	parser(t_map_client *map, int server_fd);
int	map_parse(t_map_client *map, int server_fd);

#endif