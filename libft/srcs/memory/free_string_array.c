/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hferraud <hferraud@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 11:28:00 by hferraud          #+#    #+#             */
/*   Updated: 2023/01/20 15:51:28 by hferraud         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_string_array(char **strings)
{
	size_t	i;

	i = 0;
	if (strings == NULL)
		return ;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}
