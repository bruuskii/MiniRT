/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: izouine <izouine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 22:24:03 by izouine           #+#    #+#             */
/*   Updated: 2025/01/22 22:25:10 by izouine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_add_back_pl(t_plane **objs, t_plane *node)
{
	t_plane	*tmp;

	if (!*objs)
	{
		*objs = node;
		return ;
	}
	tmp = *objs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

void	ft_add_back_cy(t_cylinder **objs, t_cylinder *node)
{
	t_cylinder	*tmp;

	if (!*objs)
	{
		*objs = node;
		return ;
	}
	tmp = *objs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

t_light	*ft_new_lt(void)
{
	t_light	*lt;

	lt = malloc(sizeof(t_light));
	if (!lt)
		return (NULL);
	lt->dir = NULL;
	lt->brightness = 0.0;
	lt->color = NULL;
	lt->type = LIGHT;
	lt->next = NULL;
	return (lt);
}

t_alight	*ft_a_light(void)
{
	t_alight	*lt;

	lt = malloc(sizeof(t_alight));
	if (!lt)
		return (NULL);
	lt->ratio = 0.0;
	lt->color = NULL;
	lt->type = ALIGHT;
	return (lt);
}

void	ft_add_back_lt(t_light **objs, t_light *node)
{
	t_light	*tmp;

	if (!*objs)
	{
		*objs = node;
		return ;
	}
	tmp = *objs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}
