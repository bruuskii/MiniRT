/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:51:47 by kbassim           #+#    #+#             */
/*   Updated: 2024/10/02 23:15:29 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt_bonus.h"

static int	ft_countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count ++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_malloc_words(char const	*s, int st, int f)
{
	int		i;
	char	*word;

	i = 0;
	word = (char *) malloc ((f - st + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (st < f)
		word[i++] = s[st++];
	word[i] = '\0';
	return (word);
}

static void	*ft_memfree(char **list, int index)
{
	int	i;

	i = index - 1;
	while (i >= 0)
	{
		free (list[i]);
		i--;
	}
	free (list);
	return (NULL);
}

static char	**ft_memalloc_list(char **list, char c, char const *s, int i)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			if (k == 0)
				k = i;
			while (s[i] && s[i] != c)
				i++;
			list[j] = ft_malloc_words(s, k, i);
			if (!list[j])
				return (ft_memfree(list, j));
			j++;
			k = 0;
		}
		else
			i++;
	}		
	list[j] = NULL;
	return (list);
}

char	**ft_split(char const *s, char c)
{
	char	**list;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	list = (char **) malloc ((ft_countwords(s, c) + 1) * sizeof(char *));
	if (!s || !list)
		return (NULL);
	return (ft_memalloc_list(list, c, s, i));
}
