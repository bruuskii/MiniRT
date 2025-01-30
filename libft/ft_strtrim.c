/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbassim <kbassim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 13:42:40 by kbassim           #+#    #+#             */
/*   Updated: 2025/01/28 11:01:09 by kbassim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

char	*ft_strtrim(char *s1, char *set)
{
	int		i;
	int		j;
	int		k;
	char	*str;
	int		len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s1);
	while (s1[i] && ft_strchr(set, s1[i]) != NULL)
		i++;
	while (j > i && ft_strchr(set, s1[j - 1]) != NULL)
		j--;
	len = j - i;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	k = 0;
	while (i < j)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}
