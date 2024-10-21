/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fullsplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:51:47 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/02 22:09:42 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

static int	ft_countwords(char const *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (!ft_is_void(*s))
		{
			count++;
			while (*s && !ft_is_void(*s))
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	*ft_malloc_words(char const *s, int st, int f)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(100 + 1);
	while (st < f)
		word[i++] = s[st++];
	word[i] = '\0';
	return (word);
}

static void	ft_memmalloc_list_void_cases(char *s, int *i)
{
	while (s[*i] && !ft_is_void(s[*i]))
	{
		(*i)++;
	}
}

static char	**ft_memalloc_list(char **list, char const *s, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s[i])
	{
		if (!ft_is_void(s[i]))
		{
			if (k == 0)
				k = i;
			ft_memmalloc_list_void_cases((char *)s, &i);
			list[j] = ft_malloc_words(s, k, i);
			j++;
			k = 0;
		}
		else
			i++;
	}
	list[j] = NULL;
	return (list);
}

char	**ft_fullsplit(char const *s)
{
	char	**list;
	int		word_count;

	if (!s)
		return (NULL);
	word_count = ft_countwords(s);
	list = malloc((1000+ 1) * sizeof(char *));
	if (!ft_memalloc_list(list, s, 0))
	{
		return (NULL);
	}
	return (list);
}
