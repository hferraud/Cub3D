/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:50:27 by edelage           #+#    #+#             */
/*   Updated: 2022/11/07 23:30:18 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	count_word(char const *s, char c)
{
	size_t	nb_word;
	size_t	index;

	index = 0;
	nb_word = 0;
	if (s == NULL)
		return (0);
	while (s[index])
	{
		while (s[index] && s[index] == c)
			index++;
		if (s[index] && s[index] != c)
		{
			nb_word++;
			while (s[index] && s[index] != c)
				index++;
		}
	}
	return (nb_word);
}

static char	*cpy_word(char const *s, char c, size_t *start)
{
	char	*word;
	size_t	len;

	len = 0;
	while (s[*start + len] && s[*start + len] != c)
		len++;
	word = (char *) malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		return (NULL);
	len = 0;
	while (s[*start + len] && s[*start + len] != c)
	{
		word[len] = s[*start + len];
		len++;
	}
	word[len] = '\0';
	*start += len;
	return (word);
}

static void	free_fresh(char **fresh, size_t n)
{
	size_t	count;

	count = 0;
	while (count < n)
	{
		free(fresh[count]);
		count++;
	}
	free(fresh);
}

static char	**fill_split(char const *s, char **fresh, char c)
{
	size_t	index_word;
	size_t	index;

	index_word = 0;
	index = 0;
	while (s[index])
	{
		while (s[index] && s[index] == c)
			index++;
		if (s[index] && s[index] != c)
		{
			fresh[index_word] = cpy_word(s, c, &index);
			if (fresh[index_word] == NULL)
			{
				free_fresh(fresh, index_word);
				return (NULL);
			}
			index_word++;
		}
	}
	fresh[index_word] = NULL;
	return (fresh);
}

char	**ft_split(char const *s, char c)
{
	char			**fresh;
	const size_t	nb_word = count_word(s, c);

	if (s == NULL)
		return (NULL);
	fresh = (char **) malloc(sizeof(char *) * (nb_word + 1));
	if (fresh == NULL)
		return (NULL);
	return (fill_split(s, fresh, c));
}
