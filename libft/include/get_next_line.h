/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:26:33 by edelage           #+#    #+#             */
/*   Updated: 2022/11/09 12:30:56 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include "libft.h"

# define BUFFER_SIZE	100

# ifndef OPEN_MAX
#  define OPEN_MAX	1024
# endif

int		strichr(const char *str, int c);
void	init_str(char *str, size_t size);
char	*get_next_line(int fd);

#endif
