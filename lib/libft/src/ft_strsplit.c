/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plamusse <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/19 22:14:03 by plamusse          #+#    #+#             */
/*   Updated: 2017/04/28 14:43:25 by plamusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char		*ft_nextword(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s == c)
		s++;
	return ((char*)s);
}

static size_t	ft_count_words(char const *s, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			j++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (j);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	nwords;
	size_t	i;

	if (s)
	{
		nwords = ft_count_words(s, c);
		if (!(tab = (char**)malloc(sizeof(char*) * (nwords + 1))))
			return (NULL);
		i = 0;
		while (i < nwords)
		{
			s = ft_nextword(s, c);
			tab[i] = ft_strsub(s, 0, ft_wordlen(s, c));
			i++;
			s = s + ft_wordlen(s, c);
		}
		tab[nwords] = NULL;
		return (tab);
	}
	return (NULL);
}
