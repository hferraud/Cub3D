/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 19:41:00 by ethan             #+#    #+#             */
/*   Updated: 2023/03/09 19:41:00 by ethan            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

int	main(int argc, char **argv)
{
	t_map	map;

	parser(argc, argv, &map);
	printf("NO: %s\n", (char *)map.wall.sprite_no);
	printf("SO: %s\n", (char *)map.wall.sprite_so);
	printf("WE: %s\n", (char *)map.wall.sprite_we);
	printf("EA: %s\n", (char *)map.wall.sprite_ea);
	printf("F: %d\n", map.floor_color);
	printf("C: %d\n", map.ceiling_color);
	return (0);
}